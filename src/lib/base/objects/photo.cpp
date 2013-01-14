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
 * @file photo.cpp
 * @brief Implementation of QFB::Photo
 */

#include "photo.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"
#include "private/photo_keys_p.h"

namespace QFB
{

class PhotoPrivate: public ObjectBasePrivate
{
public:
    explicit PhotoPrivate();
    NamedObject * from;
};

PhotoPrivate::PhotoPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

Photo::Photo(QObject *parent):
    NamedObject(parent)
{
}

Photo::Photo(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new PhotoPrivate), parent)
{
    Q_D(Photo);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create from
    QVariantMap fromData = d->propertiesMap.take(PHOTO_FROM_KEY).toMap();
    d->from = createObject<NamedObject>(fromData, this);
    // <<<<< custom object creation code
}

NamedObject * Photo::from() const
{
    Q_D(const Photo);
    // >>>>> property from
    return d->from;
    // <<<<< property from
}

QString Photo::icon() const
{
    Q_D(const Photo);
    // >>>>> property icon
    return d->propertiesMap.value(PHOTO_ICON_KEY).toString();
    // <<<<< property icon
}

QString Photo::picture() const
{
    Q_D(const Photo);
    // >>>>> property picture
    return d->propertiesMap.value(PHOTO_PICTURE_KEY).toString();
    // <<<<< property picture
}

QUrl Photo::source() const
{
    Q_D(const Photo);
    // >>>>> property source
    return parseUrl(d->propertiesMap.value(PHOTO_SOURCE_KEY).toString());
    // <<<<< property source
}

int Photo::height() const
{
    Q_D(const Photo);
    // >>>>> property height
    return d->propertiesMap.value(PHOTO_HEIGHT_KEY).toString().toInt();
    // <<<<< property height
}

int Photo::width() const
{
    Q_D(const Photo);
    // >>>>> property width
    return d->propertiesMap.value(PHOTO_WIDTH_KEY).toString().toInt();
    // <<<<< property width
}

QUrl Photo::link() const
{
    Q_D(const Photo);
    // >>>>> property link
    return parseUrl(d->propertiesMap.value(PHOTO_LINK_KEY).toString());
    // <<<<< property link
}

QDateTime Photo::createdTime() const
{
    Q_D(const Photo);
    // >>>>> property created_time
    return d->propertiesMap.value(PHOTO_CREATED_TIME_KEY).toDateTime();
    // <<<<< property created_time
}

QDateTime Photo::updatedTime() const
{
    Q_D(const Photo);
    // >>>>> property updated_time
    return d->propertiesMap.value(PHOTO_UPDATED_TIME_KEY).toDateTime();
    // <<<<< property updated_time
}

int Photo::position() const
{
    Q_D(const Photo);
    // >>>>> property position
    return d->propertiesMap.value(PHOTO_POSITION_KEY).toString().toInt();
    // <<<<< property position
}


// >>>>> custom source code
// <<<<< custom source code

}
