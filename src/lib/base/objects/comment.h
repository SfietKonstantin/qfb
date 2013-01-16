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

#ifndef QFB_COMMENT_H
#define QFB_COMMENT_H

/**
 * @file comment.h
 * @brief Definition of QFB::Comment
 */

#include "object.h"
// >>>>> includes
#include <QtCore/QDateTime>
#include "namedobject.h"
// <<<<< includes

namespace QFB {
class CommentPrivate;
/**
 * @short A comment
 *
 * This class represents a comment in Facebook.
 * Extending QFB::Object, it contains a lot of properties
 * that can be accessed through
 * - from()
 * - message()
 * - createdTime()
 * - userLikes()
 * - type()
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
 * to get a comment.
 */
class QFBBASE_EXPORT Comment: public Object
{
    Q_OBJECT
    /**
     * @short The user that created the comment
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QFB::NamedObject * from READ from CONSTANT)
    /**
     * @short The comment text
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QString message READ message CONSTANT)
    /**
     * @short The timedate the comment was created
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QDateTime createdTime READ createdTime CONSTANT)
    /**
     * @short If the authenticated user liked this comment
     * 
     * This field is returned only if the authenticated
     * user likes this comment. It is always true.
     * 
     * Requires an access token.
     */
    Q_PROPERTY(bool userLikes READ userLikes CONSTANT)
    /**
     * @short The type of this object
     * 
     * This field always returns comment.
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QString type READ type CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Comment(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Comment(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief From
     * @return from.
     */
    QFB::NamedObject * from() const;
    /**
     * @brief Message
     * @return message.
     */
    QString message() const;
    /**
     * @brief Created time
     * @return created time.
     */
    QDateTime createdTime() const;
    /**
     * @brief User likes
     * @return user likes.
     */
    bool userLikes() const;
    /**
     * @brief Type
     * @return type.
     */
    QString type() const;
private:
    Q_DECLARE_PRIVATE(Comment)
};

}

Q_DECLARE_METATYPE(QFB::Comment *)


#endif // QFB_COMMENT_H
