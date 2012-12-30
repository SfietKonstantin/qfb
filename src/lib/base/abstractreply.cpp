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
 * @file abstractreply.cpp
 * @brief Implementation of QFB::AbstractReply
 */

#include "abstractreply.h"
#include "abstractreply_p.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

namespace QFB
{

AbstractReplyPrivate::AbstractReplyPrivate(AbstractReply *q):
    q_ptr(q)
{
    reply = 0;
    isError = false;
}

QUrl AbstractReplyPrivate::redirectUrl()
{
    QUrl redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    if (redirectUrl != reply->url()) {
        return redirectUrl;
    }
    return QUrl();
}

void AbstractReplyPrivate::slotFinished()
{
    qDebug() << "Finished";

    Q_Q(AbstractReply);
    if (isError) {
        qDebug() << "Url: " << reply->url();
        qDebug() << "Received data";
        qDebug() << reply->readAll();
        return;
    }

    QUrl url = redirectUrl();
    if (!url.isEmpty()) {
        reply->deleteLater();
        reply = networkAccessManager->get(QNetworkRequest(url));
        q->connect(reply, SIGNAL(finished()), q, SLOT(slotFinished()));
        q->connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                   q, SLOT(slotError(QNetworkReply::NetworkError)));
        return;
    }
    running = false;


    if (q->processData(reply)) {
        emit q->finished();
        return;
    } else {
        emit q->failed();
        return;
    }
}

void AbstractReplyPrivate::slotError(QNetworkReply::NetworkError error)
{
    Q_Q(AbstractReply);
    running = false;
    isError = true;
    q->setError(QString("Network error %1").arg(error));
    emit q->failed();
}

////// End of private class //////

AbstractReply::AbstractReply(QObject *parent):
    QObject(parent), d_ptr(new AbstractReplyPrivate(this))
{
    Q_D(AbstractReply);
    d->networkAccessManager = 0;
    d->running = false;
}

AbstractReply::AbstractReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    QObject(parent), d_ptr(new AbstractReplyPrivate(this))
{
    Q_D(AbstractReply);
    d->networkAccessManager = networkAccessManager;
    d->running = false;
}

AbstractReply::AbstractReply(AbstractReplyPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
    Q_D(AbstractReply);
    d->networkAccessManager = 0;
    d->running = false;
}

AbstractReply::~AbstractReply()
{
}

bool AbstractReply::isRunning() const
{
    Q_D(const AbstractReply);
    return d->running;
}

QString AbstractReply::error() const
{
    Q_D(const AbstractReply);
    return d->error;
}

bool AbstractReply::preprocesssRequest()
{
    return false;
}

void AbstractReply::get(const QUrl &url)
{
    Q_D(AbstractReply);

    d->url = url;

    if (preprocesssRequest() || url.isEmpty()) {
        QEvent *event = new QEvent(QEvent::User);
        QCoreApplication::instance()->postEvent(this, event);
        return;
    }
    qDebug() << "Request url: " << url;

    d->running = true;
    d->reply = d->networkAccessManager->get(QNetworkRequest(url));
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
}

QUrl AbstractReply::url() const
{
    Q_D(const AbstractReply);
    return d->url;
}

bool AbstractReply::event(QEvent *event)
{
    if (event->type() == QEvent::User) {
        emit finished();
        return true;
    }
    return QObject::event(event);
}

void AbstractReply::setError(const QString &error)
{
    Q_D(AbstractReply);
    d->error = error;
}

}

#include "moc_abstractreply.cpp"
