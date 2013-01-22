/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 3 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 *                                                                                      *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

/**
 * @file querymanager.cpp
 * @brief Implementation of QFB::QueryManager
 */


#include "querymanager.h"
#include <QtCore/QDebug>
#include <QtCore/QMetaType>
#include <QtCore/QThreadPool>
#include "private/networkrequesthandler_p.h"
#include "private/helper_p.h"
#include "private/writablequery_p.h"
#include "processors/typeprocessor.h"
#include "processors/imageprocessor.h"
#include "processors/pictureprocessor.h"
#include "processors/objectprocessor.h"
#include "processors/objectlistprocessor.h"
#include "processors/simplecreateobjectprocessor.h"

namespace QFB
{

/**
 * @internal
 * @brief Private class for QFB::QueryManager
 */
class QueryManagerPrivate
{
public:
    explicit QueryManagerPrivate(QueryManager *q);
    WritableQuery createQuery(RequestType type);
    AbstractProcessor * createProcessor(const WritableQuery &query);
    void preparePreprocessor(AbstractProcessor *processor, const Query &query);
    Query createGraphPreprocessor(RequestType type, OperationType operation,
                                    Object::ObjectType objectType, const QString &graph,
                                    const QString &arguments,
                                    const QVariantMap &postData = QVariantMap());
    /// @todo clean mess in processor
    void slotPreprocessFinished(bool needLoading);
    void slotPreprocessError();
    void createPostprocessor(const Query &query, QIODevice *dataSource);
    void slotNetworkError(const QFB::Query &query);
    void slotPostprocessFinished();
    void slotPostprocessError();
    NetworkRequestHandler *networkRequestHandler;
    QThreadPool *processThreadPoll;
    /**
     * @internal
     * @brief Token
     */
    QString token;
    int id;
private:
    QueryManager * const q_ptr;
    Q_DECLARE_PUBLIC(QueryManager)
};

QueryManagerPrivate::QueryManagerPrivate(QueryManager *q):
    q_ptr(q)
{
    id = 0;
}

WritableQuery QueryManagerPrivate::createQuery(RequestType type)
{
    WritableQuery query (id, type);
    id ++;
    return query;
}

AbstractProcessor * QueryManagerPrivate::createProcessor(const WritableQuery &query)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = 0;
    switch(query.preprocessorData().operation()) {
    case GetOperation:
        switch(query.type()) {
        case ImageRequest:
            processor = new ImageProcessor(q);
            break;
        case PictureRequest:
            processor = new PictureProcessor(q);
            break;
        case TypeRequest:
            processor = new TypeProcessor(q);
            break;
        case ObjectRequest:
            processor = new ObjectProcessor(q);
            break;
        case ObjectListRequest:
            processor = new ObjectListProcessor(q);
            break;
        default:
            break;
        }
        break;
    case PostOperation:
        processor = new SimpleCreateObjectProcessor(q);
        break;
    default:
        break;
    }

    if (processor) {
        processor->setAutoDelete(false);
    }

    return processor;
}

void QueryManagerPrivate::preparePreprocessor(AbstractProcessor *processor, const Query &query)
{
    Q_Q(QueryManager);
    processor->setQuery(query);
    processor->setProcessingTask(AbstractProcessor::Preprocessing);
    QObject::connect(processor, SIGNAL(preprocessingFinished(bool)),
                     q, SLOT(slotPreprocessFinished(bool)));
    QObject::connect(processor, SIGNAL(error()), q, SLOT(slotPreprocessError()));
}

Query QueryManagerPrivate::createGraphPreprocessor(RequestType type, OperationType operation,
                                                     Object::ObjectType objectType,
                                                     const QString &graph, const QString &arguments,
                                                     const QVariantMap &postData)
{
    if (token.isEmpty()) {
        return Query();
    }

    WritableQuery query = createQuery(type);
    query.setObjectType(objectType);
    query.preprocessorData().setOperation(operation);
    query.preprocessorData().setGraph(graph);
    query.preprocessorData().setArguments(arguments);
    query.preprocessorData().setData(postData);

    AbstractGraphProcessor *processor
            = qobject_cast<AbstractGraphProcessor *>(createProcessor(query));
    if (!processor) {
        return Query();
    }

    preparePreprocessor(processor, query);
    processor->setToken(token);
    processThreadPoll->start(processor);

    return query;
}

void QueryManagerPrivate::slotPreprocessFinished(bool needLoading)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }
    Query query = processor->query();

    if (needLoading) {
        processor->deleteLater();
        networkRequestHandler->get(query);
    } else {
        emit q->finished(query, processor);
    }
}

void QueryManagerPrivate::slotPreprocessError()
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }

    QString errorString = processor->errorString();
    processor->deleteLater();
    emit q->error(processor->query(), errorString);
}

void QueryManagerPrivate::createPostprocessor(const Query &query, QIODevice *dataSource)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = createProcessor(WritableQuery::createWritableQuery(query));

    if (processor) {
        processor->setQuery(query);
        processor->setProcessingTask(AbstractProcessor::PostProcessing);
        processor->setDataSource(dataSource);
        QObject::connect(processor, SIGNAL(postProcessingFinished()),
                         q, SLOT(slotPostprocessFinished()));
        QObject::connect(processor, SIGNAL(error()), q, SLOT(slotPostprocessError()));
        processThreadPoll->start(processor, QThread::LowPriority);
    }
}

void QueryManagerPrivate::slotNetworkError(const Query &query)
{
    Q_Q(QueryManager);
    emit q->error(query, QObject::tr("A network error happened"));
}

void QueryManagerPrivate::slotPostprocessFinished()
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }

    Query query = processor->query();
    emit q->finished(query, processor);
}

void QueryManagerPrivate::slotPostprocessError()
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }

    Query query = processor->query();
    emit q->error(query, processor->errorString());
    processor->deleteLater();
}

////// End or private class //////

QueryManager::QueryManager(QObject *parent) :
    QObject(parent), d_ptr(new QueryManagerPrivate(this))
{
    Q_D(QueryManager);
    d->networkRequestHandler = new NetworkRequestHandler(this);
    d->processThreadPoll = new QThreadPool(this);

    qRegisterMetaType<QFB::Query>();
    connect(d->networkRequestHandler, SIGNAL(finished(QFB::Query,QIODevice*)),
            this, SLOT(createPostprocessor(QFB::Query,QIODevice*)));
    connect(d->networkRequestHandler, SIGNAL(error(QFB::Query)),
            this, SLOT(slotNetworkError(QFB::Query)));
}

QueryManager::~QueryManager()
{
    Q_D(QueryManager);
    d->networkRequestHandler->deleteLater();
}

QString QueryManager::token() const
{
    Q_D(const QueryManager);
    return d->token;
}

Query QueryManager::queryImage(const QUrl &url)
{
    Q_D(QueryManager);
    WritableQuery query = d->createQuery(ImageRequest);
    query.preprocessorData().setOperation(GetOperation);
    AbstractProcessor *processor = d->createProcessor(query);
    if (!processor) {
        return Query();
    }

    query.preprocessorData().setUrl(url);
    d->preparePreprocessor(processor, query);
    d->processThreadPoll->start(processor, 0);

    return query;
}

Query QueryManager::queryPicture(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(PictureRequest, GetOperation, Object::UnknownType,
                                      graph, arguments);
}

Query QueryManager::queryType(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(TypeRequest, GetOperation, Object::UnknownType,
                                      graph, arguments);
}

Query QueryManager::queryObject(Object::ObjectType type, const QString &graph,
                                  const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(ObjectRequest, GetOperation, type,
                                      graph, arguments);
}

Query QueryManager::queryObjectList(Object::ObjectType type, const QString &graph,
                                      const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(ObjectListRequest, GetOperation, type,
                                      graph, arguments);
}

Query QueryManager::querySimpleCreate(const QString &graph, const QVariantMap &data)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(SimplePostRequest, PostOperation, Object::UnknownType,
                                      graph, QString(), data);
}

void QueryManager::setToken(const QString &token)
{
    Q_D(QueryManager);
    if (d->token != token) {
        d->token = token;
        emit tokenChanged();
    }
}

}

#include "moc_querymanager.cpp"
