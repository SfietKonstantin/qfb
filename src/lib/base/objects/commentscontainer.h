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

#ifndef QFB_COMMENTSCONTAINER_H
#define QFB_COMMENTSCONTAINER_H

/**
 * @file commentscontainer.h
 * @brief Definition of QFB::CommentsContainer
 */

#include "objectbase.h"
// >>>>> includes
#include "comment.h"
// <<<<< includes

namespace QFB {
class CommentsContainerPrivate;
/**
 * @short A commentscontainer
 *
 * This class represents a commentscontainer in Facebook.
 * Extending QFB::ObjectBase, it contains a lot of properties
 * that can be accessed through
 * - count()
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
 * to get a commentscontainer.
 */
class QFBBASE_EXPORT CommentsContainer: public ObjectBase
{
    Q_OBJECT
    /**
     * @short Number of comments
     */
    Q_PROPERTY(int count READ count CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit CommentsContainer(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit CommentsContainer(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Count
     * @return count.
     */
    int count() const;
    /**
     * @brief Data
     * @return data.
     */
    QList<QFB::Comment *> data() const;
private:
    Q_DECLARE_PRIVATE(CommentsContainer)
};

}

Q_DECLARE_METATYPE(QFB::CommentsContainer *)


#endif // QFB_COMMENTSCONTAINER_H
