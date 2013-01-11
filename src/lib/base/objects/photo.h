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

#ifndef QFB_PHOTO_H
#define QFB_PHOTO_H

/**
 * @file photo.h
 * @brief Definition of QFB::Photo
 */

#include "namedobject.h"
#include <QtCore/QUrl>

namespace QFB
{

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

 * Some of these fields might not be set, because of
 * users hiding them in their settings, or because of
 * missing permissions.
 *
 * You can choose the fields you want using the fields
 * query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 * These parameters should be add to the query that is used
 * to get an user.
 *
 * @section missing Missing properties
 *
 * Some fields such as tags,nameTags,images
 * are not yet implemented.
 */
class QFBBASE_EXPORT Photo: public NamedObject
{
    Q_OBJECT
    /**
     * @short The profile (user or page) that posted this photo
     */
    Q_PROPERTY(NamedObject * from READ from CONSTANT)
    /// @todo tags
    /// @todo name_tags
    /**
     * @short The icon that Facebook displays when photos are published to the Feed
     */
    Q_PROPERTY(QString icon READ icon CONSTANT)
    /**
     * @short The thumbnail-sized source of the photo
     */
    Q_PROPERTY(QString picture READ picture CONSTANT)
    /**
     * @short The source image of the photo
     * 
     * Currently this can have a maximum width or height of 720px,
     * increasing to 960px on 1st March 2012.
     */
    Q_PROPERTY(QUrl source READ source CONSTANT)
    /**
     * @short The height of the photo in pixels
     */
    Q_PROPERTY(int height READ height CONSTANT)
    /**
     * @short The width of the photo in pixels
     */
    Q_PROPERTY(int width READ width CONSTANT)
    /// @todo images
    /**
     * @short A link to the photo on Facebook
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
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
    explicit Photo(const PropertiesMap propertiesMap, QObject *parent = 0);
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
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::Photo *)

#endif // QFB_PHOTO_H
