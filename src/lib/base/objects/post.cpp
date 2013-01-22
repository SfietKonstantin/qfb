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
 * @file post.cpp
 * @brief Implementation of QFB::Post
 */

#include "post.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief POST_FROM_KEY
 */
static const char *POST_FROM_KEY = "from";
/**
 * @internal
 * @brief POST_TO_KEY
 */
static const char *POST_TO_KEY = "to";
/**
 * @internal
 * @brief POST_MESSAGE_KEY
 */
static const char *POST_MESSAGE_KEY = "message";
/**
 * @internal
 * @brief POST_PICTURE_KEY
 */
static const char *POST_PICTURE_KEY = "picture";
/**
 * @internal
 * @brief POST_LINK_KEY
 */
static const char *POST_LINK_KEY = "link";
/**
 * @internal
 * @brief POST_CAPTION_KEY
 */
static const char *POST_CAPTION_KEY = "caption";
/**
 * @internal
 * @brief POST_DESCRIPTION_KEY
 */
static const char *POST_DESCRIPTION_KEY = "description";
/**
 * @internal
 * @brief POST_SOURCE_KEY
 */
static const char *POST_SOURCE_KEY = "source";
/**
 * @internal
 * @brief POST_ICON_KEY
 */
static const char *POST_ICON_KEY = "icon";
/**
 * @internal
 * @brief POST_TYPE_KEY
 */
static const char *POST_TYPE_KEY = "type";
/**
 * @internal
 * @brief POST_LIKES_KEY
 */
static const char *POST_LIKES_KEY = "likes";
/**
 * @internal
 * @brief POST_STORY_KEY
 */
static const char *POST_STORY_KEY = "story";
/**
 * @internal
 * @brief POST_COMMENTS_KEY
 */
static const char *POST_COMMENTS_KEY = "comments";
/**
 * @internal
 * @brief POST_OBJECT_ID_KEY
 */
static const char *POST_OBJECT_ID_KEY = "object_id";
/**
 * @internal
 * @brief POST_APPLICATION_KEY
 */
static const char *POST_APPLICATION_KEY = "application";
/**
 * @internal
 * @brief POST_CREATED_TIME_KEY
 */
static const char *POST_CREATED_TIME_KEY = "created_time";
/**
 * @internal
 * @brief POST_UPDATED_TIME_KEY
 */
static const char *POST_UPDATED_TIME_KEY = "updated_time";


/**
 * @internal
 * @short Private class for QFB::Post
 */
class PostPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit PostPrivate();
    /**
     * @internal
     * @short From
     */
    QFB::NamedObject * from;
    /**
     * @internal
     * @short List of to
     */
    QList<QFB::NamedObject *> to;
    /**
     * @internal
     * @short Likes
     */
    QFB::LikesContainer * likes;
    /**
     * @internal
     * @short Comments
     */
    QFB::CommentsContainer * comments;
    /**
     * @internal
     * @short Application
     */
    QFB::NamedObject * application;
};

PostPrivate::PostPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

Post::Post(QObject *parent):
    NamedObject(parent)
{
}

Post::Post(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new PostPrivate), parent)
{
    Q_D(Post);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create from
    QVariantMap fromData = d->propertiesMap.take(POST_FROM_KEY).toMap();
    d->from = createObject<QFB::NamedObject>(fromData, this);
    // Create to
    QVariantList toData = d->propertiesMap.take(POST_TO_KEY).toList();
    d->to = createList<QFB::NamedObject>(toData, this);
    // Create likes
    QVariantMap likesData = d->propertiesMap.take(POST_LIKES_KEY).toMap();
    d->likes = createObject<QFB::LikesContainer>(likesData, this);
    // Create comments
    QVariantMap commentsData = d->propertiesMap.take(POST_COMMENTS_KEY).toMap();
    d->comments = createObject<QFB::CommentsContainer>(commentsData, this);
    // Create application
    QVariantMap applicationData = d->propertiesMap.take(POST_APPLICATION_KEY).toMap();
    d->application = createObject<QFB::NamedObject>(applicationData, this);
    // <<<<< custom object creation code
}

QFB::NamedObject * Post::from() const
{
    Q_D(const Post);
    // >>>>> property from
    return d->from;
    // <<<<< property from
}

QList<QFB::NamedObject *> Post::to() const
{
    Q_D(const Post);
    // >>>>> property to
    return d->to;
    // <<<<< property to
}

QString Post::message() const
{
    Q_D(const Post);
    // >>>>> property message
    return d->propertiesMap.value(POST_MESSAGE_KEY).toString();
    // <<<<< property message
}

QUrl Post::picture() const
{
    Q_D(const Post);
    // >>>>> property picture
    return parseUrl(d->propertiesMap.value(POST_PICTURE_KEY).toString());
    // <<<<< property picture
}

QUrl Post::link() const
{
    Q_D(const Post);
    // >>>>> property link
    return parseUrl(d->propertiesMap.value(POST_LINK_KEY).toString());
    // <<<<< property link
}

QString Post::caption() const
{
    Q_D(const Post);
    // >>>>> property caption
    return d->propertiesMap.value(POST_CAPTION_KEY).toString();
    // <<<<< property caption
}

QString Post::description() const
{
    Q_D(const Post);
    // >>>>> property description
    return d->propertiesMap.value(POST_DESCRIPTION_KEY).toString();
    // <<<<< property description
}

QUrl Post::source() const
{
    Q_D(const Post);
    // >>>>> property source
    return parseUrl(d->propertiesMap.value(POST_SOURCE_KEY).toString());
    // <<<<< property source
}

QUrl Post::icon() const
{
    Q_D(const Post);
    // >>>>> property icon
    return parseUrl(d->propertiesMap.value(POST_ICON_KEY).toString());
    // <<<<< property icon
}

QString Post::type() const
{
    Q_D(const Post);
    // >>>>> property type
    return d->propertiesMap.value(POST_TYPE_KEY).toString();
    // <<<<< property type
}

QFB::LikesContainer * Post::likes() const
{
    Q_D(const Post);
    // >>>>> property likes
    return d->likes;
    // <<<<< property likes
}

QString Post::story() const
{
    Q_D(const Post);
    // >>>>> property story
    return d->propertiesMap.value(POST_STORY_KEY).toString();
    // <<<<< property story
}

QFB::CommentsContainer * Post::comments() const
{
    Q_D(const Post);
    // >>>>> property comments
    return d->comments;
    // <<<<< property comments
}

QString Post::objectId() const
{
    Q_D(const Post);
    // >>>>> property object_id
    return d->propertiesMap.value(POST_OBJECT_ID_KEY).toString();
    // <<<<< property object_id
}

QFB::NamedObject * Post::application() const
{
    Q_D(const Post);
    // >>>>> property application
    return d->application;
    // <<<<< property application
}

QDateTime Post::createdTime() const
{
    Q_D(const Post);
    // >>>>> property created_time
    return d->propertiesMap.value(POST_CREATED_TIME_KEY).toDateTime();
    // <<<<< property created_time
}

QDateTime Post::updatedTime() const
{
    Q_D(const Post);
    // >>>>> property updated_time
    return d->propertiesMap.value(POST_UPDATED_TIME_KEY).toDateTime();
    // <<<<< property updated_time
}


// >>>>> custom source code
// <<<<< custom source code

}
