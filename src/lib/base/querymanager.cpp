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
#include "request.h"
#include "private/networkrequesthandler_p.h"
#include "private/helper_p.h"
#include "processors/typeprocessor.h"
#include "processors/imageprocessor.h"
#include "processors/pictureprocessor.h"
#include "processors/objectprocessor.h"
#include "processors/objectlistprocessor.h"
//#include "processors/albumprocessor.h"
//#include "processors/albumlistprocessor.h"
//#include "processors/feedprocessor.h"
//#include "processors/friendlistprocessor.h"
//#include "processors/photolistprocessor.h"
//#include "processors/userprocessor.h"
//#include "processors/poststatusprocessor.h"

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
    Request createRequest(RequestType type);
    AbstractProcessor * createProcessor(const Request &request);
    void preparePreprocessor(AbstractProcessor *processor, const Request &request);
    Request createGraphPreprocessor(RequestType type, OperationType operation,
                                    Object::ObjectType objectType, const QString &graph,
                                    const QString &arguments,
                                    const QVariantMap &postData = QVariantMap());
    /// @todo clean mess in processor
    void slotPreprocessFinished(bool needLoading);
    void slotPreprocessError();
    void createPostprocessor(const Request &request, QIODevice *dataSource);
    void slotNetworkError(const QFB::Request &request);
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

Request QueryManagerPrivate::createRequest(RequestType type)
{
    Request request (id, type);
    id ++;
    return request;
}

AbstractProcessor * QueryManagerPrivate::createProcessor(const Request &request)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = 0;

    switch(request.preprocessorData().operation()) {
    case GetOperation:
        switch(request.type()) {
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
        }
    default:
        break;
    }

    if (processor) {
        processor->setAutoDelete(false);
    }

    return processor;
}

void QueryManagerPrivate::preparePreprocessor(AbstractProcessor *processor, const Request &request)
{
    Q_Q(QueryManager);
    processor->setRequest(request);
    processor->setProcessingTask(AbstractProcessor::Preprocessing);
    QObject::connect(processor, SIGNAL(preprocessingFinished(bool)),
                     q, SLOT(slotPreprocessFinished(bool)));
    QObject::connect(processor, SIGNAL(error()), q, SLOT(slotPreprocessError()));
}

Request QueryManagerPrivate::createGraphPreprocessor(RequestType type, OperationType operation,
                                                     Object::ObjectType objectType,
                                                     const QString &graph, const QString &arguments,
                                                     const QVariantMap &postData)
{
    if (token.isEmpty()) {
        return Request();
    }

    Request request = createRequest(type);
    request.setObjectType(objectType);
    request.preprocessorData().setOperation(operation);
    request.preprocessorData().setGraph(graph);
    request.preprocessorData().setArguments(arguments);
    request.preprocessorData().setData(postData);

    AbstractGraphProcessor *processor
            = qobject_cast<AbstractGraphProcessor *>(createProcessor(request));
    if (!processor) {
        return Request();
    }

    preparePreprocessor(processor, request);
    processor->setToken(token);
    processThreadPoll->start(processor);

    return request;
}

void QueryManagerPrivate::slotPreprocessFinished(bool needLoading)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }
    Request request = processor->request();

    if (needLoading) {
        processor->deleteLater();
        networkRequestHandler->get(request);
    } else {
        emit q->finished(request, processor);
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
    emit q->error(processor->request(), errorString);
}

void QueryManagerPrivate::createPostprocessor(const Request &request, QIODevice *dataSource)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = createProcessor(request);

    if (processor) {
        processor->setRequest(request);
        processor->setProcessingTask(AbstractProcessor::PostProcessing);
        processor->setDataSource(dataSource);
        QObject::connect(processor, SIGNAL(postProcessingFinished()),
                         q, SLOT(slotPostprocessFinished()));
        QObject::connect(processor, SIGNAL(error()), q, SLOT(slotPostprocessError()));
        processThreadPoll->start(processor, QThread::LowPriority);
    }
}

void QueryManagerPrivate::slotNetworkError(const Request &request)
{
    Q_Q(QueryManager);
    emit q->error(request, QObject::tr("A network error happened"));
}

void QueryManagerPrivate::slotPostprocessFinished()
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }

    Request request = processor->request();
    emit q->finished(request, processor);
}

void QueryManagerPrivate::slotPostprocessError()
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }

    Request request = processor->request();
    emit q->error(request, processor->errorString());
    processor->deleteLater();
}

////// End or private class //////

QueryManager::QueryManager(QObject *parent) :
    QObject(parent), d_ptr(new QueryManagerPrivate(this))
{
    Q_D(QueryManager);
    d->networkRequestHandler = new NetworkRequestHandler(this);
    d->processThreadPoll = new QThreadPool(this);

    qRegisterMetaType<QFB::Request>();
    connect(d->networkRequestHandler, SIGNAL(finished(QFB::Request,QIODevice*)),
            this, SLOT(createPostprocessor(QFB::Request,QIODevice*)));
    connect(d->networkRequestHandler, SIGNAL(error(QFB::Request)),
            this, SLOT(slotNetworkError(QFB::Request)));
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

Request QueryManager::queryImage(const QUrl &url)
{
    Q_D(QueryManager);
    Request request = d->createRequest(ImageRequest);
    request.preprocessorData().setOperation(GetOperation);
    AbstractProcessor *processor = d->createProcessor(request);
    if (!processor) {
        return Request();
    }

    request.preprocessorData().setUrl(url);
    d->preparePreprocessor(processor, request);
    d->processThreadPoll->start(processor, 0);

    return request;
}

Request QueryManager::queryPicture(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(PictureRequest, GetOperation, Object::UnknownType,
                                      graph, arguments);
}

Request QueryManager::queryType(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(TypeRequest, GetOperation, Object::UnknownType,
                                      graph, arguments);
}

Request QueryManager::queryObject(Object::ObjectType type, const QString &graph,
                                  const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(ObjectRequest, GetOperation, type,
                                      graph, arguments);
}

Request QueryManager::queryObjectList(Object::ObjectType type, const QString &graph,
                                      const QString &arguments)
{
    Q_D(QueryManager);
    return d->createGraphPreprocessor(ObjectListRequest, GetOperation, type,
                                      graph, arguments);
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
