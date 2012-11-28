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

#include "querymanager.h"
#include "friendlistreply.h"

#include <QtNetwork/QNetworkAccessManager>

namespace QFB
{

class QueryManagerPrivate
{
public:
    QNetworkAccessManager *networkAccessManager;
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

FriendListReply * QueryManager::queryFriends(const QString &graph)
{
    Q_D(QueryManager);
    if (d->token.isEmpty()) {
        return 0;
    }

    FriendListReply *reply = new FriendListReply(d->networkAccessManager, this);
    reply->request(graph, d->token);
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
