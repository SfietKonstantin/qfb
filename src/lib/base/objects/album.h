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

#ifndef QFB_ALBUM_H
#define QFB_ALBUM_H

/**
 * @file album.h
 * @brief Definition of QFB::Album
 */

#include "namedobject.h"
#include <QtCore/QDateTime>
#include <QtCore/QUrl>

namespace QFB
{

/**
 * @short An album
 * 
 * This class represents an album in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - from()
 * - description()
 * - location()
 * - link()
 * - coverPhoto()
 * - count()
 * - type()
 * - createdTime()
 * - updatedTime()
 * - canUpload()

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
 * Some fields such as privacy
 * are not yet implemented.
 */
class QFBBASE_EXPORT Album: public NamedObject
{
    Q_OBJECT
    /**
     * @short The profile that created this album
     */
    Q_PROPERTY(NamedObject * from READ from CONSTANT)
    /**
     * @short The description of the album
     */
    Q_PROPERTY(QString description READ description CONSTANT)
    /**
     * @short The location of the album
     */
    Q_PROPERTY(QString location READ location CONSTANT)
    /**
     * @short A link to this album on Facebook
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
    /**
     * @short The album cover photo ID
     */
    Q_PROPERTY(QString coverPhoto READ coverPhoto CONSTANT)
    /// @todo privacy
    /**
     * @short The number of photos in this album
     */
    Q_PROPERTY(int count READ count CONSTANT)
    /**
     * @short The type of the album
     * 
     * The type can be: profile, mobile, wall, normal or album
     */
    Q_PROPERTY(QString type READ type CONSTANT)
    /**
     * @short The time the photo album was initially created
     */
    Q_PROPERTY(QDateTime createdTime READ createdTime CONSTANT)
    /**
     * @short The last time the photo album was updated
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    /**
     * @short If the user can upload to that album
     * 
     * Determines whether the UID can upload to the album and returns
     * true if the user owns the album, the album is not full, and
     * the app can add photos to the album.
     */
    Q_PROPERTY(bool canUpload READ canUpload CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Album(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Album(const PropertiesMap propertiesMap, QObject *parent = 0);
    /**
     * @brief From
     * @return from.
     */
    NamedObject * from() const;
    /**
     * @brief Description
     * @return description.
     */
    QString description() const;
    /**
     * @brief Location
     * @return location.
     */
    QString location() const;
    /**
     * @brief Link
     * @return link.
     */
    QUrl link() const;
    /**
     * @brief Cover photo
     * @return cover photo.
     */
    QString coverPhoto() const;
    /**
     * @brief Count
     * @return count.
     */
    int count() const;
    /**
     * @brief Type
     * @return type.
     */
    QString type() const;
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
     * @brief Can upload
     * @return can upload.
     */
    bool canUpload() const;
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::Album *)

#endif // QFB_ALBUM_H
