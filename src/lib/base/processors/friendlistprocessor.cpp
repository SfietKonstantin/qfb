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

#include "friendlistprocessor.h"
#include <QtCore/QCoreApplication>
#include "private/abstractpagingprocessor_p.h"
#include "private/helper_p.h"
#include "private/jsonhelper_p.h"
#include "private/namedobject_keys_p.h"
#include "private/object_keys_p.h"
#include "private/paging_keys_p.h"
#include "objects/namedobject.h"

namespace QFB
{

/**
 * @internal
 * @brief DATA_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *DATA_KEY = "data";

class FriendListProcessorPrivate: public AbstractPagingProcessorPrivate
{
public:
    explicit FriendListProcessorPrivate();
    /**
     * @internal
     * @brief Friend list
     */
    QList<NamedObject *> friendList;
};

FriendListProcessorPrivate::FriendListProcessorPrivate():
    AbstractPagingProcessorPrivate()
{
}

////// End of private class //////

FriendListProcessor::FriendListProcessor(QObject *parent):
    AbstractPagingProcessor(*(new FriendListProcessorPrivate()), parent)
{
}

QList<NamedObject *> FriendListProcessor::friendList() const
{
    Q_D(const FriendListProcessor);
    return d->friendList;
}

bool FriendListProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(FriendListProcessor);

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

    JsonArray dataArray = QFB_JSON_GET_ARRAY(rootObject.value(DATA_KEY));

    foreach (JsonValue value, dataArray) {
        if (QFB_JSON_IS_OBJECT(value)) {
            JsonObject object = QFB_JSON_GET_OBJECT(value);
            if (object.contains(OBJECT_ID_KEY) && object.contains(NAMEDOBJECT_NAME_KEY)) {
                QString id = object.value(OBJECT_ID_KEY).toString();
                QString name = object.value(NAMEDOBJECT_NAME_KEY).toString();
                PropertiesMap propertiesMap;
                propertiesMap.insert(OBJECT_ID_KEY, id);
                propertiesMap.insert(NAMEDOBJECT_NAME_KEY, name);
                NamedObject *userBase = new NamedObject(propertiesMap);
                userBase->moveToThread(QCoreApplication::instance()->thread());
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