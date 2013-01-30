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
 * @file groupbookmark.cpp
 * @brief Implementation of QFB::GroupBookmark
 */

#include "groupbookmark.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief GROUPBOOKMARK_VERSION_KEY
 */
static const char *GROUPBOOKMARK_VERSION_KEY = "version";
/**
 * @internal
 * @brief GROUPBOOKMARK_BOOKMARK_ORDER_KEY
 */
static const char *GROUPBOOKMARK_BOOKMARK_ORDER_KEY = "bookmark_order";
/**
 * @internal
 * @brief GROUPBOOKMARK_UNREAD_KEY
 */
static const char *GROUPBOOKMARK_UNREAD_KEY = "unread";


/**
 * @internal
 * @short Private class for QFB::GroupBookmark
 */
class GroupBookmarkPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit GroupBookmarkPrivate();
};

GroupBookmarkPrivate::GroupBookmarkPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

GroupBookmark::GroupBookmark(QObject *parent):
    NamedObject(parent)
{
}

GroupBookmark::GroupBookmark(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new GroupBookmarkPrivate), parent)
{
    Q_D(GroupBookmark);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // <<<<< custom object creation code
}

int GroupBookmark::version() const
{
    Q_D(const GroupBookmark);
    // >>>>> property version
    return d->propertiesMap.value(GROUPBOOKMARK_VERSION_KEY).toString().toInt();
    // <<<<< property version
}

int GroupBookmark::bookmarkOrder() const
{
    Q_D(const GroupBookmark);
    // >>>>> property bookmark_order
    return d->propertiesMap.value(GROUPBOOKMARK_BOOKMARK_ORDER_KEY).toString().toInt();
    // <<<<< property bookmark_order
}

int GroupBookmark::unread() const
{
    Q_D(const GroupBookmark);
    // >>>>> property unread
    return d->propertiesMap.value(GROUPBOOKMARK_UNREAD_KEY).toString().toInt();
    // <<<<< property unread
}


// >>>>> custom source code
// <<<<< custom source code

}
