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

#include "base_global.h"
#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QMetaType>
#include <QtCore/QSharedData>
#include <QtCore/QUrl>
#include "qfb.h"
#include "objects/object.h"
#include "preprocessordata.h"

namespace QFB
{

struct QueryPrivate: public QSharedData
{
    int id;
    PreprocessorData preprocessorData;
    RequestType type;
    Object::ObjectType objectType;
};

/**
 * @brief Informations about a query
 *
 *
 */
class QFBBASE_EXPORT Query
{
public:
    explicit Query();
    explicit Query(int id, RequestType type);
    Query(const Query &other);
    virtual ~Query();
    bool operator==(const Query &other) const;
    bool operator!=(const Query &other) const;
    bool isValid() const;
    int id() const;
    PreprocessorData preprocessorData() const;
    PreprocessorData & preprocessorData();
    RequestType type() const;
    Object::ObjectType objectType() const;
    void setId(int id);
    void setPreprocessorData(const PreprocessorData &preprocessorData);
    void setType(RequestType type);
    void setObjectType(Object::ObjectType objectType);
private:
    QExplicitlySharedDataPointer<QueryPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Query)
};

}

Q_DECLARE_METATYPE(QFB::Query)

#endif // QFB_QUERY_H
