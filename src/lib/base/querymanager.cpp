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
#include "networkrequesthandler_p.h"
#include "helper_p.h"
#include "request.h"
#include "friendlistprocessor.h"
#include "userprocessor.h"

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
    void createProcessor(const Request & request, QIODevice *dataSource);
    void slotNetworkError(const QFB::Request &request);
    void slotProcessFinished();
    void slotProcessError();
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

void QueryManagerPrivate::createProcessor(const Request &request, QIODevice *dataSource)
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = 0;
    switch (request.type()) {
    case FriendListRequest:
        processor = new FriendListProcessor(q);
        break;
    case UserRequest:
        processor = new UserProcessor(q);
        break;
    default:
        break;
    }

    if (processor) {
        processor->setAutoDelete(false);
        processor->setRequest(request);
        processor->setDataSource(dataSource);
        QObject::connect(processor, SIGNAL(finished()), q, SLOT(slotProcessFinished()));
        QObject::connect(processor, SIGNAL(error()), q, SLOT(slotProcessError()));
        processThreadPoll->start(processor, QThread::LowPriority);
    }
}

void QueryManagerPrivate::slotNetworkError(const Request &request)
{
    Q_Q(QueryManager);
    emit q->error(request, QObject::tr("A network error happened"));
}

void QueryManagerPrivate::slotProcessFinished()
{
    Q_Q(QueryManager);
    AbstractProcessor *processor = qobject_cast<AbstractProcessor *>(q->sender());
    if (!processor) {
        return;
    }

    Request request = processor->request();
    emit q->finished(request, processor);
}

void QueryManagerPrivate::slotProcessError()
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
            this, SLOT(createProcessor(QFB::Request,QIODevice*)));
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

//ImageReply * QueryManager::queryImage(const QUrl &url)
//{
//    Q_D(QueryManager);
//    ImageReply *reply = new ImageReply(d->networkAccessManager, this);
//    reply->request(url);
//    return reply;
//}

Request QueryManager::queryFriendList(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    Request request;
    if (d->token.isEmpty()) {
        return request;
    }
    request = d->createRequest(FriendListRequest);
    d->networkRequestHandler->get(request, graphUrl(graph, d->token, createArguments(arguments)));
    return request;
}

//PictureReply * QueryManager::queryPicture(const QString &graph, const QString &arguments)
//{
//    Q_D(QueryManager);
//    if (d->token.isEmpty()) {
//        return 0;
//    }

//    PictureReply *reply = new PictureReply(d->networkAccessManager, this);
//    reply->request(graph, d->token, arguments);
//    return reply;
//}

Request QueryManager::queryUser(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    Request request;
    if (d->token.isEmpty()) {
        return request;
    }
    request = d->createRequest(UserRequest);
    d->networkRequestHandler->get(request, graphUrl(graph, d->token, createArguments(arguments)));
    return request;
}

//FeedReply * QueryManager::queryFeed(const QString &graph, const QString &arguments)
//{
//    Q_D(QueryManager);
//    if (d->token.isEmpty()) {
//        return 0;
//    }

//    FeedReply *reply = new FeedReply(d->networkAccessManager, this);
//    reply->request(graph, d->token, arguments);
//    return reply;
//}

//TypeReply * QueryManager::queryType(const QString &graph, const QString &arguments)
//{
//    Q_D(QueryManager);
//    if (d->token.isEmpty()) {
//        return 0;
//    }

//    TypeReply *reply = new TypeReply(d->networkAccessManager, this);
//    reply->request(graph, d->token, arguments);
//    return reply;
//}

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
