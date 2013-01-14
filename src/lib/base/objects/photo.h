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

#ifndef QFB_PHOTO_H
#define QFB_PHOTO_H

/**
 * @file photo.h
 * @brief Definition of QFB::Photo
 */

#include "namedobject.h"
// >>>>> includes
#include <QtCore/QUrl>
#include <QtCore/QDateTime>
// <<<<< includes

namespace QFB {
class PhotoPrivate;
/**
 * @short A photo
 *
 * This class represents a photo in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - from()
 * - icon()
 * - picture()
 * - source()
 * - height()
 * - width()
 * - link()
 * - createdTime()
 * - updatedTime()
 * - position()
 *
 * Some of these fields might not be set, because of
 * users hiding them in their settings, or because of
 * missing permissions.
 *
 * You can choose the fields you want using the "fields"
 * query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 *
 * These parameters should be added to the query that is used
 * to get a photo.
 *
 * @section missing Missing properties
 *
 * Some fields such as tags, nameTags, images, place
 * are not yet implemented.
 */
class QFBBASE_EXPORT Photo: public NamedObject
{
    Q_OBJECT
    /**
     * @short The profile (user or page) that posted this photo
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(NamedObject * from READ from CONSTANT)
    /// @todo tags
    /// @todo name_tags
    /**
     * @short The icon that Facebook displays when photos are published to the Feed
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(QString icon READ icon CONSTANT)
    /**
     * @short The thumbnail-sized source of the photo
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(QString picture READ picture CONSTANT)
    /**
     * @short The source image of the photo
     * 
     * Currently this can have a maximum width or height of 720px,
     * increasing to 960px on 1st March 2012.
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(QUrl source READ source CONSTANT)
    /**
     * @short The height of the photo in pixels
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(int height READ height CONSTANT)
    /**
     * @short The width of the photo in pixels
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(int width READ width CONSTANT)
    /// @todo images
    /**
     * @short A link to the photo on Facebook
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
    /// @todo place
    /**
     * @short The time the photo was initially published
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(QDateTime createdTime READ createdTime CONSTANT)
    /**
     * @short The last time the photo or its caption was updated
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    /**
     * @short The position of this photo in the album
     * 
     * Requires an access token or \e user_photos
     * or \e friend_photos.
     */
    Q_PROPERTY(int position READ position CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Photo(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Photo(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief From
     * @return from.
     */
    NamedObject * from() const;
    /**
     * @brief Icon
     * @return icon.
     */
    QString icon() const;
    /**
     * @brief Picture
     * @return picture.
     */
    QString picture() const;
    /**
     * @brief Source
     * @return source.
     */
    QUrl source() const;
    /**
     * @brief Height
     * @return height.
     */
    int height() const;
    /**
     * @brief Width
     * @return width.
     */
    int width() const;
    /**
     * @brief Link
     * @return link.
     */
    QUrl link() const;
    /**
     * @brief Created time
     * @return created time.
     */
    QDateTime createdTime() const;
    /**
     * @brief Updated time
     * @return updated time.
     */
    QDateTime updatedTime() const;
    /**
     * @brief Position
     * @return position.
     */
    int position() const;
private:
    Q_DECLARE_PRIVATE(Photo)
};

}

Q_DECLARE_METATYPE(QFB::Photo *)


#endif // QFB_PHOTO_H
