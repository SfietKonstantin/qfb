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

namespace QFB
{

/**
 * @internal
 * @brief PHOTO_FROM_KEY
 */
static const char *PHOTO_FROM_KEY = "from";
/**
 * @internal
 * @brief PHOTO_ICON_KEY
 */
static const char *PHOTO_ICON_KEY = "icon";
/**
 * @internal
 * @brief PHOTO_PICTURE_KEY
 */
static const char *PHOTO_PICTURE_KEY = "picture";
/**
 * @internal
 * @brief PHOTO_SOURCE_KEY
 */
static const char *PHOTO_SOURCE_KEY = "source";
/**
 * @internal
 * @brief PHOTO_HEIGHT_KEY
 */
static const char *PHOTO_HEIGHT_KEY = "height";
/**
 * @internal
 * @brief PHOTO_WIDTH_KEY
 */
static const char *PHOTO_WIDTH_KEY = "width";
/**
 * @internal
 * @brief PHOTO_IMAGES_KEY
 */
static const char *PHOTO_IMAGES_KEY = "images";
/**
 * @internal
 * @brief PHOTO_LINK_KEY
 */
static const char *PHOTO_LINK_KEY = "link";
/**
 * @internal
 * @brief PHOTO_CREATED_TIME_KEY
 */
static const char *PHOTO_CREATED_TIME_KEY = "created_time";
/**
 * @internal
 * @brief PHOTO_UPDATED_TIME_KEY
 */
static const char *PHOTO_UPDATED_TIME_KEY = "updated_time";
/**
 * @internal
 * @brief PHOTO_POSITION_KEY
 */
static const char *PHOTO_POSITION_KEY = "position";


/**
 * @internal
 * @short Private class for QFB::Photo
 */
class PhotoPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit PhotoPrivate();
    /**
     * @internal
     * @short From
     */
    NamedObject * from;
    /**
     * @internal
     * @short List of images
     */
    QList<PhotoInformations *> images;
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
    // Create images
    QVariantList imagesData = d->propertiesMap.take(PHOTO_IMAGES_KEY).toList();
    d->images = createList<PhotoInformations>(imagesData, this);
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

QList<PhotoInformations *> Photo::images() const
{
    Q_D(const Photo);
    // >>>>> property images
    return d->images;
    // <<<<< property images
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
