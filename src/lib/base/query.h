/****************************************************************************************
 * Copyright (C) 2012 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef QFB_QUERY_H
#define QFB_QUERY_H

/**
 * @file query.h
 * @brief Definition of QFB::Query
 */

#include "base_global.h"
#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QMetaType>
#include <QtCore/QSharedData>
#include <QtCore/QUrl>
#include "qfb.h"
#include "objects/object.h"

namespace QFB
{

/**
 * @internal
 * @brief Data associated to QFB::Query
 */
struct QueryPrivate: public QSharedData
{
    /**
     * @internal
     * @brief Id of the query
     */
    int id;
    /**
     * @internal
     * @brief Request type
     */
    RequestType type;
    /**
     * @internal
     * @brief Object type
     */
    Object::ObjectType objectType;
};

/**
 * @brief Informations about a query
 *
 * This class contains all the information that is related
 * to a query. All queries have an unique id, that can be
 * accessed through id(). They also contain the type of query
 * that is being done (get, post etc.) and the type of
 * object that is expected to be received.
 *
 * This class is explicitely shared.
 */
class QFBBASE_EXPORT Query
{
public:
    /**
     * @brief Invalid constructor
     */
    explicit Query();
    /**
     * @brief Copy constructor
     * @param other other query.
     */
    Query(const Query &other);
    /**
     * @brief Destructor
     */
    virtual ~Query();
    /**
     * @brief Comparison
     * @param other other query.
     * @return if the two queries are equal.
     */
    bool operator==(const Query &other) const;
    /**
     * @brief Comparison
     * @param other other query.
     * @return if the two queries are different.
     */
    bool operator!=(const Query &other) const;
    /**
     * @brief If the query is valid
     * @return if the query is valid.
     */
    bool isValid() const;
    /**
     * @brief Id of the query
     * @return id of the query.
     */
    int id() const;
    /**
     * @brief Request type
     * @return request type.
     */
    RequestType type() const;
    /**
     * @brief Object type
     * @return object type.
     */
    Object::ObjectType objectType() const;
protected:
    Query(QueryPrivate &dd);
    /**
     * @brief D-pointer
     */
    QExplicitlySharedDataPointer<QueryPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Query)
};

}

Q_DECLARE_METATYPE(QFB::Query)

#endif // QFB_QUERY_H
