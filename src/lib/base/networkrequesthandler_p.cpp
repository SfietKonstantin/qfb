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

class NetworkRequestHandlerPrivate
{
public:
    explicit NetworkRequestHandlerPrivate(NetworkRequestHandler *q);
    static QUrl redirectUrl(QNetworkReply *reply);
    void slotFinished();
    QNetworkAccessManager *networkAccessManager;
    QMap<QNetworkReply *, Request> replies;
private:
    NetworkRequestHandler * const q_ptr;
    Q_DECLARE_PUBLIC(NetworkRequestHandler)
};

NetworkRequestHandlerPrivate::NetworkRequestHandlerPrivate(NetworkRequestHandler *q):
    q_ptr(q)
{
    networkAccessManager = 0;
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
        return;
    }

    QUrl redirect = redirectUrl(reply);
    if (!redirect.isEmpty()) {
        q->get(request, redirect);
        return;
    }

    qDebug() << reply->url();
    emit q->finished(request, reply);
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

void NetworkRequestHandler::get(const Request &request, const QUrl &url)
{
    Q_D(NetworkRequestHandler);
    QNetworkReply *reply = d->networkAccessManager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    d->replies.insert(reply, request);
}

}

#include "moc_networkrequesthandler_p.cpp"
