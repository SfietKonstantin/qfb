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
#include "friendlistreply.h"
#include "picturereply.h"
#include "userreply.h"

#include <QtNetwork/QNetworkAccessManager>

namespace QFB
{

/**
 * @internal
 * @brief Private class for QFB::QueryManager
 */
class QueryManagerPrivate
{
public:
    /**
     * @internal
     * @brief Network access manager
     */
    QNetworkAccessManager *networkAccessManager;
    /**
     * @internal
     * @brief Token
     */
    QString token;
};

////// End or private class //////

QueryManager::QueryManager(QObject *parent) :
    QObject(parent), d_ptr(new QueryManagerPrivate())
{
    Q_D(QueryManager);
    d->networkAccessManager = new QNetworkAccessManager(this);
}

QueryManager::~QueryManager()
{
}

QString QueryManager::token() const
{
    Q_D(const QueryManager);
    return d->token;
}

FriendListReply * QueryManager::queryFriendList(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    if (d->token.isEmpty()) {
        return 0;
    }

    FriendListReply *reply = new FriendListReply(d->networkAccessManager, this);
    reply->request(graph, d->token, arguments);
    return reply;
}

PictureReply * QueryManager::queryPicture(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    if (d->token.isEmpty()) {
        return 0;
    }

    PictureReply *reply = new PictureReply(d->networkAccessManager, this);
    reply->request(graph, d->token, arguments);
    return reply;
}

UserReply * QueryManager::queryUser(const QString &graph, const QString &arguments)
{
    Q_D(QueryManager);
    if (d->token.isEmpty()) {
        return 0;
    }

    UserReply *reply = new UserReply(d->networkAccessManager, this);
    reply->request(graph, d->token, arguments);
    return reply;
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
