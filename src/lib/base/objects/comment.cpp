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
 * @file comment.cpp
 * @brief Implementation of QFB::Comment
 */

#include "comment.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief COMMENT_FROM_KEY
 */
static const char *COMMENT_FROM_KEY = "from";
/**
 * @internal
 * @brief COMMENT_MESSAGE_KEY
 */
static const char *COMMENT_MESSAGE_KEY = "message";
/**
 * @internal
 * @brief COMMENT_CREATED_TIME_KEY
 */
static const char *COMMENT_CREATED_TIME_KEY = "created_time";
/**
 * @internal
 * @brief COMMENT_USER_LIKES_KEY
 */
static const char *COMMENT_USER_LIKES_KEY = "user_likes";
/**
 * @internal
 * @brief COMMENT_TYPE_KEY
 */
static const char *COMMENT_TYPE_KEY = "type";


/**
 * @internal
 * @short Private class for QFB::Comment
 */
class CommentPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit CommentPrivate();
    /**
     * @internal
     * @short From
     */
    QFB::NamedObject * from;
};

CommentPrivate::CommentPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

Comment::Comment(QObject *parent):
    Object(parent)
{
}

Comment::Comment(const QVariantMap propertiesMap, QObject *parent):
    Object(*(new CommentPrivate), parent)
{
    Q_D(Comment);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create from
    QVariantMap fromData = d->propertiesMap.take(COMMENT_FROM_KEY).toMap();
    d->from = createObject<QFB::NamedObject>(fromData, this);
    // <<<<< custom object creation code
}

QFB::NamedObject * Comment::from() const
{
    Q_D(const Comment);
    // >>>>> property from
    return d->from;
    // <<<<< property from
}

QString Comment::message() const
{
    Q_D(const Comment);
    // >>>>> property message
    return d->propertiesMap.value(COMMENT_MESSAGE_KEY).toString();
    // <<<<< property message
}

QDateTime Comment::createdTime() const
{
    Q_D(const Comment);
    // >>>>> property created_time
    return d->propertiesMap.value(COMMENT_CREATED_TIME_KEY).toDateTime();
    // <<<<< property created_time
}

bool Comment::userLikes() const
{
    Q_D(const Comment);
    // >>>>> property user_likes
    return d->propertiesMap.value(COMMENT_USER_LIKES_KEY).toBool();
    // <<<<< property user_likes
}

QString Comment::type() const
{
    Q_D(const Comment);
    // >>>>> property type
    return d->propertiesMap.value(COMMENT_TYPE_KEY).toString();
    // <<<<< property type
}


// >>>>> custom source code
// <<<<< custom source code

}
