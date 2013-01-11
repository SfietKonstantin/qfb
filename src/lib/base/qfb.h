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

#ifndef QFB_QFB_H
#define QFB_QFB_H

/**
 * @file qfb.h
 * @short Global enumerations used in qfb
 */

#include <QtCore/QMap>
#include <QtCore/QVariant>

namespace QFB
{
/**
 * @brief Properties map
 *
 * This typedef defines a mapping between a proprety name,
 * that is the string used in Facebook to identify a property,
 * and the value of that property.
 */
typedef QMap<QString, QVariant> PropertiesMap;

/**
 * @brief Enumeration describing the request type
 */
enum RequestType {
    /**
     * @short An invalid request
     */
    InvalidRequest,
    /**
     * @short A request for an image
     */
    ImageRequest,
    /**
     * @short A request to get the type of an object
     */
    TypeRequest,
    /**
     * @short A request to get a list of friends
     */
    FriendListRequest,
    /**
     * @short A request to get an user
     */
    UserRequest,
    /**
     * @short A request to get a Facebook picture
     */
    PictureRequest,
    /**
     * @short A request to get a feed
     */
    FeedRequest,
    /**
     * @short A request to get an album
     */
    AlbumRequest,
    /**
     * @short A request to get a list of albums
     */
    AlbumListRequest,
    /**
     * @short A request to get a list of photos
     */
    PhotoListRequest
};

enum OperationType {
    InvalidOperation, GetOperation, PostOperation, DeleteOperation
};

}

#endif // QFB_QFB_H
