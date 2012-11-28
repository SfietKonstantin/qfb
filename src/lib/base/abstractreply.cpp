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

#include <QtCore/QtGlobal>
#include <QtCore/QDebug>
#include <QtCore/QUrl>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtCore/QUrlQuery>
#endif
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

namespace QFB
{

/**
 * @brief FB_GRAPH_QUERY_URL
 *
 * Used in QFB::AbstractReply.
 */
static const char *FB_GRAPH_QUERY_URL = "https://graph.facebook.com/";
/**
 * @brief FB_GRAPH_QUERY_TOKEN_KEY
 *
 * Used in QFB::AbstractReply.
 */
static const char *FB_GRAPH_QUERY_TOKEN_KEY = "access_token";

AbstractReplyPrivate::AbstractReplyPrivate(AbstractReply *q):
    q_ptr(q)
{
    reply = 0;
}

void AbstractReplyPrivate::slotFinished()
{
    Q_Q(AbstractReply);
    if (q->processData(reply)) {
        emit q->finished();
    } else {
        emit q->error();
    }
}

void AbstractReplyPrivate::slotError(QNetworkReply::NetworkError error)
{
    Q_UNUSED(error)
    Q_Q(AbstractReply);
    emit q->error();
}

////// End of private class //////

AbstractReply::AbstractReply(QObject *parent):
    QObject(parent), d_ptr(new AbstractReplyPrivate(this))
{
    Q_D(AbstractReply);
    d->networkAccessManager = 0;
}

AbstractReply::AbstractReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    QObject(parent), d_ptr(new AbstractReplyPrivate(this))
{
    Q_D(AbstractReply);
    d->networkAccessManager = networkAccessManager;
}

AbstractReply::AbstractReply(AbstractReplyPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
    Q_D(AbstractReply);
    d->networkAccessManager = 0;
}

AbstractReply::~AbstractReply()
{
}

void AbstractReply::request(const QString &graph, const QString &token)
{
    Q_D(AbstractReply);
    if (d->reply) {
        return;
    }
    QString urlString = QString(FB_GRAPH_QUERY_URL);
    urlString.append(graph);
    QUrl url (urlString);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    url.addQueryItem(FB_GRAPH_QUERY_TOKEN_KEY, token);
#else
    QUrlQuery urlQuery;
    urlQuery.addQueryItem(FB_GRAPH_QUERY_TOKEN_KEY, token);
    url.setQuery(urlQuery);
#endif

    d->reply = d->networkAccessManager->get(QNetworkRequest(url));
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(slotError(QNetworkReply::NetworkError)));
}

}

#include "moc_abstractreply.cpp"
