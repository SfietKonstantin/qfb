/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @file album.cpp
 * @brief Implementation of QFB::Album
 */

#include "album.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"
#include "private/album_keys_p.h"

namespace QFB
{

/**
 * @internal
 * @short Private class for QFB::Album
 */
class AlbumPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit AlbumPrivate();
    /**
     * @internal
     * @short From
     */
    NamedObject * from;
};

AlbumPrivate::AlbumPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

Album::Album(QObject *parent):
    NamedObject(parent)
{
}

Album::Album(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new AlbumPrivate), parent)
{
    Q_D(Album);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create from
    QVariantMap fromData = d->propertiesMap.take(ALBUM_FROM_KEY).toMap();
    d->from = createObject<NamedObject>(fromData, this);
    // <<<<< custom object creation code
}

NamedObject * Album::from() const
{
    Q_D(const Album);
    // >>>>> property from
    return d->from;
    // <<<<< property from
}

QString Album::description() const
{
    Q_D(const Album);
    // >>>>> property description
    return d->propertiesMap.value(ALBUM_DESCRIPTION_KEY).toString();
    // <<<<< property description
}

QString Album::location() const
{
    Q_D(const Album);
    // >>>>> property location
    return d->propertiesMap.value(ALBUM_LOCATION_KEY).toString();
    // <<<<< property location
}

QUrl Album::link() const
{
    Q_D(const Album);
    // >>>>> property link
    return parseUrl(d->propertiesMap.value(ALBUM_LINK_KEY).toString());
    // <<<<< property link
}

QString Album::coverPhoto() const
{
    Q_D(const Album);
    // >>>>> property cover_photo
    return d->propertiesMap.value(ALBUM_COVER_PHOTO_KEY).toString();
    // <<<<< property cover_photo
}

int Album::count() const
{
    Q_D(const Album);
    // >>>>> property count
    return d->propertiesMap.value(ALBUM_COUNT_KEY).toString().toInt();
    // <<<<< property count
}

QString Album::type() const
{
    Q_D(const Album);
    // >>>>> property type
    return d->propertiesMap.value(ALBUM_TYPE_KEY).toString();
    // <<<<< property type
}

QDateTime Album::createdTime() const
{
    Q_D(const Album);
    // >>>>> property created_time
    return d->propertiesMap.value(ALBUM_CREATED_TIME_KEY).toDateTime();
    // <<<<< property created_time
}

QDateTime Album::updatedTime() const
{
    Q_D(const Album);
    // >>>>> property updated_time
    return d->propertiesMap.value(ALBUM_UPDATED_TIME_KEY).toDateTime();
    // <<<<< property updated_time
}

bool Album::canUpload() const
{
    Q_D(const Album);
    // >>>>> property can_upload
    return d->propertiesMap.value(ALBUM_CAN_UPLOAD_KEY).toBool();
    // <<<<< property can_upload
}


// >>>>> custom source code
// <<<<< custom source code

}
