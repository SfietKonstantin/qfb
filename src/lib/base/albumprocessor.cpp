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

#include "albumprocessor.h"
#include "albumprocessor_p.h"
#include <QtCore/QCoreApplication>
#include "album.h"
#include "album_keys_p.h"
#include "helper_p.h"
#include "namedobject_keys_p.h"
#include "object_keys_p.h"

namespace QFB
{

AlbumProcessorPrivate::AlbumProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    album = 0;
}

Album * AlbumProcessorPrivate::createAlbum(const JsonObject &jsonObject)
{
    PropertiesMap propertiesMap;
    propertiesMap.insert(OBJECT_ID_KEY, jsonObject.value(OBJECT_ID_KEY).toString());
    propertiesMap.insert(NAMEDOBJECT_NAME_KEY, jsonObject.value(NAMEDOBJECT_NAME_KEY).toString());

    PropertiesMap fromPropertiesMap;
    JsonObject fromObject = QFB_JSON_GET_OBJECT(jsonObject.value(ALBUM_FROM_KEY));
    fromPropertiesMap.insert(OBJECT_ID_KEY, fromObject.value(OBJECT_ID_KEY).toString());
    fromPropertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                             fromObject.value(NAMEDOBJECT_NAME_KEY).toString());
    propertiesMap.insert(ALBUM_FROM_KEY,
                         QVariant::fromValue(new NamedObject(fromPropertiesMap)));
    propertiesMap.insert(ALBUM_DESCRIPTION_KEY, jsonObject.value(ALBUM_DESCRIPTION_KEY).toString());
    propertiesMap.insert(ALBUM_LOCATION_KEY, jsonObject.value(ALBUM_LOCATION_KEY).toString());
    propertiesMap.insert(ALBUM_LINK_KEY, parseUrl(jsonObject.value(ALBUM_LINK_KEY).toString()));
    propertiesMap.insert(ALBUM_COVER_PHOTO_KEY, jsonObject.value(ALBUM_COVER_PHOTO_KEY).toString());
    propertiesMap.insert(ALBUM_COUNT_KEY, (int) jsonObject.value(ALBUM_COUNT_KEY).toDouble());
    propertiesMap.insert(ALBUM_TYPE_KEY, jsonObject.value(ALBUM_TYPE_KEY).toString());
    QDateTime createdTime
            = QDateTime::fromString(jsonObject.value(ALBUM_CREATED_TIME_KEY).toString(),
                                    Qt::ISODate);
    propertiesMap.insert(ALBUM_CREATED_TIME_KEY, createdTime);
    QDateTime updatedTime
            = QDateTime::fromString(jsonObject.value(ALBUM_UPDATED_TIME_KEY).toString(),
                                    Qt::ISODate);
    propertiesMap.insert(ALBUM_UPDATED_TIME_KEY, updatedTime);
    propertiesMap.insert(ALBUM_CAN_UPLOAD_KEY, jsonObject.value(ALBUM_CAN_UPLOAD_KEY).toBool());

    Album *album = new Album(propertiesMap);
    album->moveToThread(QCoreApplication::instance()->thread());
    return album;
}

////// End of private class //////

AlbumProcessor::AlbumProcessor(QObject *parent):
    AbstractGraphProcessor(*(new AlbumProcessorPrivate), parent)
{
}

Album * AlbumProcessor::album() const
{
    Q_D(const AlbumProcessor);
    return d->album;
}

bool AlbumProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(AlbumProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);
    d->album = d->createAlbum(rootObject);
    if (d->album) {
        return true;
    } else {
        return false;
    }
}

}
