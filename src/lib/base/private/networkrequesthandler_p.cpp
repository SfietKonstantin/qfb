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
#include "request.h"

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
    QMap<QNetworkReply *, Request> replies;
    int runningReplies;
    QList<Request> queue;
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

    // Check the request
    if (!replies.contains(reply)) {
        qDebug() << "Error: reply is unknown";
        return;
    }

    Request request = replies.value(reply);
    replies.remove(reply);

    // Check the error
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error: encountered network error" << reply->error();
        qDebug() << reply->errorString();

        qDebug() << reply->readAll();
        reply->deleteLater();

        emit q->error(request);
        removeReply();
        return;
    }

    QUrl redirect = redirectUrl(reply);
    if (!redirect.isEmpty()) {
        request.setUrl(redirect);
        q->get(request);
        removeReply();
        return;
    }

    emit q->finished(request, reply);
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
        Request nextRequest = queue.takeFirst();
        QNetworkReply *reply = networkAccessManager->get(QNetworkRequest(nextRequest.url()));
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

void NetworkRequestHandler::get(const Request &request)
{
    Q_D(NetworkRequestHandler);
    d->queue.append(request);
    d->scheduleReplies();
}

}

#include "moc_networkrequesthandler_p.cpp"
