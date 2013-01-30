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

#ifndef QFB_GROUP_H
#define QFB_GROUP_H

/**
 * @file group.h
 * @brief Definition of QFB::Group
 */

#include "namedobject.h"
// >>>>> includes
#include <QtCore/QDateTime>
#include <QtCore/QUrl>
// <<<<< includes

namespace QFB {
class GroupPrivate;
/**
 * @short A group
 *
 * This class represents a group in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - version()
 * - icon()
 * - owner()
 * - description()
 * - link()
 * - updatedTime()
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
 * to get a group.
 *
 * @section missing Missing properties
 *
 * Some fields such as privacy
 * are not yet implemented.
 */
class QFBBASE_EXPORT Group: public NamedObject
{
    Q_OBJECT
    /**
     * @short A flag for the version
     * 
     * This flag indicates if the group was created prior to
     * launch of the current groups product in October 2010.
     * 
     * 0 indicates an old group, 1 a newer group and 3 a top-level
     * school group.
     * 
     * Requires an access token and \e user_groups or \e friend_groups.
     */
    Q_PROPERTY(int version READ version CONSTANT)
    /**
     * @short The URL for the group's icon
     * 
     * Requires an access token and \e user_groups or \e friend_groups.
     */
    Q_PROPERTY(QUrl icon READ icon CONSTANT)
    /**
     * @short The profile that created this group
     * 
     * Requires an access token and \e user_groups or \e friend_groups.
     */
    Q_PROPERTY(QFB::NamedObject * owner READ owner CONSTANT)
    /**
     * @short A brief description of the group
     * 
     * Requires an access token and \e user_groups or \e friend_groups.
     */
    Q_PROPERTY(QString description READ description CONSTANT)
    /**
     * @short The URL for the group's website
     * 
     * Requires an access token and \e user_groups or \e friend_groups.
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
    /// @todo privacy
    /**
     * @short The last time the group was updated
     * 
     * Requires an access token and \e user_groups or \e friend_groups.
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Group(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Group(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Version
     * @return version.
     */
    int version() const;
    /**
     * @brief Icon
     * @return icon.
     */
    QUrl icon() const;
    /**
     * @brief Owner
     * @return owner.
     */
    QFB::NamedObject * owner() const;
    /**
     * @brief Description
     * @return description.
     */
    QString description() const;
    /**
     * @brief Link
     * @return link.
     */
    QUrl link() const;
    /**
     * @brief Updated time
     * @return updated time.
     */
    QDateTime updatedTime() const;
private:
    Q_DECLARE_PRIVATE(Group)
};

}

Q_DECLARE_METATYPE(QFB::Group *)


#endif // QFB_GROUP_H
