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

#ifndef QFB_WRITABLEQUERY_P_H
#define QFB_WRITABLEQUERY_P_H

#include "query.h"
#include "preprocessordata_p.h"

namespace QFB
{

class WritableQueryPrivate: public QueryPrivate
{
public:
    /**
     * @internal
     * @brief Preprocessor data
     */
    PreprocessorData preprocessorData;
};

class WritableQuery: public Query
{
public:
    explicit WritableQuery();
    /**
     * @brief Default constructor
     * @param id id of the query.
     * @param type type of the query.
     */
    explicit WritableQuery(int id, RequestType type);
    WritableQuery(const WritableQuery &other);
    static WritableQuery createWritableQuery(const Query &query);
    /**
     * @brief Preprocessor data
     * @return preprocessor data.
     */
    PreprocessorData preprocessorData() const;
    /**
     * @brief Preprocessor data
     * @return preprocessor data.
     */
    PreprocessorData & preprocessorData();
    /**
     * @brief Set the id of the query.
     * @param id id of the query to set.
     */
    void setId(int id);
    /**
     * @brief Set the request type
     * @param type request type to set.
     */
    void setType(RequestType type);
    /**
     * @brief Set the object type
     * @param objectType object type to set.
     */
    void setObjectType(Object::ObjectType objectType);
private:
    WritableQuery(const Query &query);
    Q_DECLARE_PRIVATE(WritableQuery)
};

}

#endif // QFB_WRITABLEQUERY_P_H
