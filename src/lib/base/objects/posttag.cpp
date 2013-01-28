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
 * @file posttag.cpp
 * @brief Implementation of QFB::PostTag
 */

#include "posttag.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief POSTTAG_OFFSET_KEY
 */
static const char *POSTTAG_OFFSET_KEY = "offset";
/**
 * @internal
 * @brief POSTTAG_LENGTH_KEY
 */
static const char *POSTTAG_LENGTH_KEY = "length";


/**
 * @internal
 * @short Private class for QFB::PostTag
 */
class PostTagPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit PostTagPrivate();
};

PostTagPrivate::PostTagPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

PostTag::PostTag(QObject *parent):
    NamedObject(parent)
{
}

PostTag::PostTag(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new PostTagPrivate), parent)
{
    Q_D(PostTag);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // <<<<< custom object creation code
}

int PostTag::offset() const
{
    Q_D(const PostTag);
    // >>>>> property offset
    return d->propertiesMap.value(POSTTAG_OFFSET_KEY).toString().toInt();
    // <<<<< property offset
}

int PostTag::length() const
{
    Q_D(const PostTag);
    // >>>>> property length
    return d->propertiesMap.value(POSTTAG_LENGTH_KEY).toString().toInt();
    // <<<<< property length
}


// >>>>> custom source code
// <<<<< custom source code

}
