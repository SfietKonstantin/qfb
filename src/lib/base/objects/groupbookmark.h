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

#ifndef QFB_GROUPBOOKMARK_H
#define QFB_GROUPBOOKMARK_H

/**
 * @file groupbookmark.h
 * @brief Definition of QFB::GroupBookmark
 */

#include "namedobject.h"
// >>>>> includes
// <<<<< includes

namespace QFB {
class GroupBookmarkPrivate;
/**
 * @short A groupbookmark
 *
 * This class represents a groupbookmark in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - version()
 * - bookmarkOrder()
 * - unread()
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
 * to get a groupbookmark.
 *
 * @section missing Missing properties
 *
 * Some fields such as administrator
 * are not yet implemented.
 */
class QFBBASE_EXPORT GroupBookmark: public NamedObject
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
     */
    Q_PROPERTY(int version READ version CONSTANT)
    /**
     * @short Bookmark order
     */
    Q_PROPERTY(int bookmarkOrder READ bookmarkOrder CONSTANT)
    /**
     * @short Number of unread entries
     */
    Q_PROPERTY(int unread READ unread CONSTANT)
    /// @todo administrator
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit GroupBookmark(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit GroupBookmark(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Version
     * @return version.
     */
    int version() const;
    /**
     * @brief Bookmark order
     * @return bookmark order.
     */
    int bookmarkOrder() const;
    /**
     * @brief Unread
     * @return unread.
     */
    int unread() const;
private:
    Q_DECLARE_PRIVATE(GroupBookmark)
};

}

Q_DECLARE_METATYPE(QFB::GroupBookmark *)


#endif // QFB_GROUPBOOKMARK_H
