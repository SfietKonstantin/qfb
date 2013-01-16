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

#ifndef QFB_LIKESCONTAINER_H
#define QFB_LIKESCONTAINER_H

/**
 * @file likescontainer.h
 * @brief Definition of QFB::LikesContainer
 */

#include "objectbase.h"
// >>>>> includes
#include "namedobject.h"
// <<<<< includes

namespace QFB {
class LikesContainerPrivate;
/**
 * @short A likes container
 *
 * This class represents a likes container in Facebook.
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
 * to get a likes container.
 */
class QFBBASE_EXPORT LikesContainer: public ObjectBase
{
    Q_OBJECT
    /**
     * @short Number of likes
     */
    Q_PROPERTY(int count READ count CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit LikesContainer(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit LikesContainer(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Count
     * @return count.
     */
    int count() const;
    /**
     * @brief Data
     * @return data.
     */
    QList<QFB::NamedObject *> data() const;
private:
    Q_DECLARE_PRIVATE(LikesContainer)
};

}

Q_DECLARE_METATYPE(QFB::LikesContainer *)


#endif // QFB_LIKESCONTAINER_H
