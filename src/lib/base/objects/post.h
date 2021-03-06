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

#ifndef QFB_POST_H
#define QFB_POST_H

/**
 * @file post.h
 * @brief Definition of QFB::Post
 */

#include "namedobject.h"
// >>>>> includes
#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include "commentscontainer.h"
#include "likescontainer.h"
#include "posttag.h"
// <<<<< includes

namespace QFB {
class PostPrivate;
/**
 * @short A post
 *
 * This class represents a post in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - from()
 * - message()
 * - picture()
 * - link()
 * - caption()
 * - description()
 * - source()
 * - icon()
 * - type()
 * - likes()
 * - story()
 * - comments()
 * - objectId()
 * - application()
 * - createdTime()
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
 * to get a post.
 *
 * @section missing Missing properties
 *
 * Some fields such as properties, actions, privacy, place
 * are not yet implemented.
 *
 * @section notImplemented Not implemented
 *
 * Fields includeHidden
 * will not be implemented.
 */
class QFBBASE_EXPORT Post: public NamedObject
{
    Q_OBJECT
    /**
     * @short Information about the user who posted the message
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QFB::NamedObject * from READ from CONSTANT)
    /**
     * @short The message
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QString message READ message CONSTANT)
    /**
     * @short If available, a link to the picture included with this post
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QUrl picture READ picture CONSTANT)
    /**
     * @short The link attached to this post
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
    /**
     * @short The caption of the link
     * 
     * This entry appears beneath the link name.
     * Requires an access token.
     */
    Q_PROPERTY(QString caption READ caption CONSTANT)
    /**
     * @short A description of the link
     * 
     * This entry appears beneath the link caption.
     * Requires an access token.
     */
    Q_PROPERTY(QString description READ description CONSTANT)
    /**
     * @short A URL to a Flash movie or video file to be embedded within the post
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QUrl source READ source CONSTANT)
    /// @todo properties
    /**
     * @short A link to an icon representing the type of this post
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QUrl icon READ icon CONSTANT)
    /// @todo actions
    /// @todo privacy
    /**
     * @short A string indicating the type for this post
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QString type READ type CONSTANT)
    /**
     * @short Likes for this post
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QFB::LikesContainer * likes READ likes CONSTANT)
    /// @todo place
    /**
     * @short Text of stories not intentionally generated by users
     * 
     * The stories are like those generated when two users become friends.
     * you must have the "Include recent activity stories" migration enabled
     * in your app to retrieve these stories.
     * 
     * Requires \e read_stream.
     */
    Q_PROPERTY(QString story READ story CONSTANT)
    /**
     * @short Comments for this post
     * 
     * Requires \e read_stream.
     */
    Q_PROPERTY(QFB::CommentsContainer * comments READ comments CONSTANT)
    /**
     * @short The Facebook object id for an uploaded photo or video
     * 
     * Requires \e read_stream.
     */
    Q_PROPERTY(QString objectId READ objectId CONSTANT)
    /**
     * @short Information about the application this post came from
     * 
     * Requires \e read_stream.
     */
    Q_PROPERTY(QFB::NamedObject * application READ application CONSTANT)
    /**
     * @short The time the post was initially published
     * 
     * Requires \e read_stream.
     */
    Q_PROPERTY(QDateTime createdTime READ createdTime CONSTANT)
    /**
     * @short The time of the last comment on this post
     * 
     * Requires \e read_stream.
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    // include_hidden will not be implemented
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Post(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Post(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief From
     * @return from.
     */
    QFB::NamedObject * from() const;
    /**
     * @brief To
     * @return to.
     */
    QList<QFB::NamedObject *> to() const;
    /**
     * @brief Message
     * @return message.
     */
    QString message() const;
    /**
     * @brief Message tags
     * @return message tags.
     */
    QList<QFB::PostTag *> messageTags() const;
    /**
     * @brief Picture
     * @return picture.
     */
    QUrl picture() const;
    /**
     * @brief Link
     * @return link.
     */
    QUrl link() const;
    /**
     * @brief Caption
     * @return caption.
     */
    QString caption() const;
    /**
     * @brief Description
     * @return description.
     */
    QString description() const;
    /**
     * @brief Source
     * @return source.
     */
    QUrl source() const;
    /**
     * @brief Icon
     * @return icon.
     */
    QUrl icon() const;
    /**
     * @brief Type
     * @return type.
     */
    QString type() const;
    /**
     * @brief Likes
     * @return likes.
     */
    QFB::LikesContainer * likes() const;
    /**
     * @brief Story
     * @return story.
     */
    QString story() const;
    /**
     * @brief With tags
     * @return with tags.
     */
    QList<QFB::NamedObject *> withTags() const;
    /**
     * @brief Comments
     * @return comments.
     */
    QFB::CommentsContainer * comments() const;
    /**
     * @brief Object id
     * @return object id.
     */
    QString objectId() const;
    /**
     * @brief Application
     * @return application.
     */
    QFB::NamedObject * application() const;
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
private:
    Q_DECLARE_PRIVATE(Post)
};

}

Q_DECLARE_METATYPE(QFB::Post *)


#endif // QFB_POST_H
