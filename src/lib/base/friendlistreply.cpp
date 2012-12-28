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
 * @file friendlistreply.cpp
 * @brief Implementation of QFB::FriendListReply
 */

#include "friendlistreply.h"
#include "abstractgraphpagingreply_p.h"

#include <QtCore/QDebug>
#include <QtCore/QIODevice>
#include <QtCore/QVariant>

#include "helper_p.h"
#include "jsonhelper_p.h"
#include "namedobject.h"

namespace QFB
{

/**
 * @internal
 * @brief DATA_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *DATA_KEY = "data";
/**
 * @internal
 * @brief NAME_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *NAME_KEY = "name";
/**
 * @internal
 * @brief ID_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *ID_KEY = "id";
/**
 * @internal
 * @brief PAGING_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *PAGING_KEY = "paging";
/**
 * @internal
 * @brief PAGING_NEXT_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *PAGING_NEXT_KEY = "next";

/**
 * @internal
 * @brief Private class for QFB::FriendListReplyPrivate
 */
class FriendListReplyPrivate: public AbstractGraphPagingReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    FriendListReplyPrivate(FriendListReply *q);
    /**
     * @internal
     * @brief Friend list
     */
    QList<NamedObject *> friendList;
private:
    Q_DECLARE_PUBLIC(FriendListReply)
};

FriendListReplyPrivate::FriendListReplyPrivate(FriendListReply *q):
    AbstractGraphPagingReplyPrivate(q)
{
}

////// End of private class //////

FriendListReply::FriendListReply(QObject *parent):
    AbstractGraphPagingReply(*(new FriendListReplyPrivate(this)), parent)
{
}

FriendListReply::FriendListReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractGraphPagingReply(*(new FriendListReplyPrivate(this)), parent)
{
    Q_D(FriendListReply);
    d->networkAccessManager = networkAccessManager;
}

QList<NamedObject *> FriendListReply::friendList() const
{
    Q_D(const FriendListReply);
    return d->friendList;
}

bool FriendListReply::processData(QIODevice *dataSource)
{
    Q_D(FriendListReply);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);

    if (!rootObject.contains(DATA_KEY)) {
        setError("Received data do not contains correct data.");
        return false;
    }

    qDeleteAll(d->friendList);
    d->friendList.clear();

    JsonArray dataArray = QFB_JSON_GET_ARRAY(rootObject.value(DATA_KEY));

    foreach (JsonValue value, dataArray) {
        if (QFB_JSON_IS_OBJECT(value)) {
            JsonObject object = QFB_JSON_GET_OBJECT(value);
            if (object.contains(ID_KEY) && object.contains(NAME_KEY)) {
                QString id = object.value(ID_KEY).toString();
                QString name = object.value(NAME_KEY).toString();
                PropertiesMap propertiesMap;
                propertiesMap.insert(IdProperty, id);
                propertiesMap.insert(NameProperty, name);
                NamedObject *userBase = new NamedObject(propertiesMap, this);
                d->friendList.append(userBase);
            }
        }
    }

    JsonObject pagingObject = QFB_JSON_GET_OBJECT(rootObject.value(PAGING_KEY));
    QUrl nextPageUrl = parseUrl(pagingObject.value(PAGING_NEXT_KEY).toString());
    setNextPageUrl(nextPageUrl);

    return true;
}

}
