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

#include "networkrequesthandler_p.h"
#include <QtCore/QDebug>
#include <QtCore/QMap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "private/writablequery_p.h"

namespace QFB
{

static const int MAX_REPLIES = 3;

class NetworkRequestHandlerPrivate
{
public:
    explicit NetworkRequestHandlerPrivate(NetworkRequestHandler *q);
    static QUrl redirectUrl(QNetworkReply *reply);
    void slotFinished();
    void removeReply();
    void scheduleReplies();
    QNetworkAccessManager *networkAccessManager;
    QMap<QNetworkReply *, WritableQuery> replies;
    int runningReplies;
    QList<WritableQuery> queue;
private:
    NetworkRequestHandler * const q_ptr;
    Q_DECLARE_PUBLIC(NetworkRequestHandler)
};

NetworkRequestHandlerPrivate::NetworkRequestHandlerPrivate(NetworkRequestHandler *q):
    q_ptr(q)
{
    networkAccessManager = 0;
    runningReplies = 0;
}

QUrl NetworkRequestHandlerPrivate::redirectUrl(QNetworkReply *reply)
{
    QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (redirectUrl != reply->url()) {
        return redirectUrl;
    }
    return QUrl();
}

void NetworkRequestHandlerPrivate::slotFinished()
{
    Q_Q(NetworkRequestHandler);
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(q->sender());
    if (!reply) {
        return;
    }

    if (!replies.contains(reply)) {
        qDebug() << "Error: reply is unknown";
        return;
    }

    WritableQuery query = replies.value(reply);
    replies.remove(reply);

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: encountered network error" << reply->error();
        qDebug() << reply->errorString();

        qDebug() << reply->readAll();
        reply->deleteLater();

        emit q->error(query);
        removeReply();
        return;
    }

    QUrl redirect = redirectUrl(reply);
    if (!redirect.isEmpty()) {
        query.preprocessorData().setUrl(redirect);
        q->get(query);
        removeReply();
        return;
    }

    emit q->finished(query, reply);
    removeReply();
}

void NetworkRequestHandlerPrivate::removeReply()
{
    runningReplies --;
    scheduleReplies();
}

void NetworkRequestHandlerPrivate::scheduleReplies()
{
    Q_Q(NetworkRequestHandler);
    while (runningReplies < MAX_REPLIES && !queue.isEmpty()) {
        WritableQuery nextRequest = queue.takeFirst();
        QUrl url = nextRequest.preprocessorData().url();
        QNetworkReply *reply = 0;
        switch (nextRequest.preprocessorData().operation()) {
        case GetOperation:
            reply = networkAccessManager->get(QNetworkRequest(url));
            break;
        case PostOperation:
            reply = networkAccessManager->post(QNetworkRequest(url),
                                               nextRequest.preprocessorData().postData());
            break;
        case DeleteOperation:
            reply = networkAccessManager->deleteResource(QNetworkRequest(url));
            break;
        default:
            qFatal("Invalid operation");
        }

        QObject::connect(reply, SIGNAL(finished()), q, SLOT(slotFinished()));
        replies.insert(reply, nextRequest);
        runningReplies ++;
    }
}

////// End of private class //////

NetworkRequestHandler::NetworkRequestHandler(QObject *parent) :
    QObject(parent), d_ptr(new NetworkRequestHandlerPrivate(this))
{
    Q_D(NetworkRequestHandler);
    d->networkAccessManager = new QNetworkAccessManager();
}

NetworkRequestHandler::~NetworkRequestHandler()
{
    Q_D(NetworkRequestHandler);
    d->networkAccessManager->deleteLater();
}

void NetworkRequestHandler::get(const Query &query)
{
    Q_D(NetworkRequestHandler);
    d->queue.append(WritableQuery::createWritableQuery(query));
    d->scheduleReplies();
}

}

#include "moc_networkrequesthandler_p.cpp"
