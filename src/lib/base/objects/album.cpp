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
 * @file album.cpp
 * @brief Implementation of QFB::Album
 */

#include "album.h"
#include "private/objectbase_p.h"
#include "private/album_keys_p.h"
namespace QFB
{

Album::Album(QObject *parent):
    NamedObject(parent)
{
}

Album::Album(const PropertiesMap propertiesMap, QObject *parent):
    NamedObject(propertiesMap, parent)
{
    Q_D(ObjectBase);

    // TODO: check reparenting
    // It was done automatically by a script

    // Reparent from
    QObject *fromObject = d->propertiesMap.value(ALBUM_FROM_KEY).value<NamedObject *>();
    if (fromObject) {
        fromObject->setParent(this);
    }

}
NamedObject * Album::from() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_FROM_KEY).value<NamedObject *>();
}

QString Album::description() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_DESCRIPTION_KEY).toString();
}

QString Album::location() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_LOCATION_KEY).toString();
}

QUrl Album::link() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_LINK_KEY).toUrl();
}

QString Album::coverPhoto() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_COVER_PHOTO_KEY).toString();
}

int Album::count() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_COUNT_KEY).toInt();
}

QString Album::type() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_TYPE_KEY).toString();
}

QDateTime Album::createdTime() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_CREATED_TIME_KEY).toDateTime();
}

QDateTime Album::updatedTime() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_UPDATED_TIME_KEY).toDateTime();
}

bool Album::canUpload() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(ALBUM_CAN_UPLOAD_KEY).toBool();
}

}
