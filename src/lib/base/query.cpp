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

/**
 * @file query.cpp
 * @brief Implementation of QFB::Query
 */

#include "query.h"
#include "private/helper_p.h"

namespace QFB
{

Query::Query():
    d_ptr(new QueryPrivate)
{
    setId(-1);
    setType(InvalidRequest);
    setObjectType(Object::UnknownType);
}

Query::Query(int id, RequestType type):
    d_ptr(new QueryPrivate)
{
    setId(id);
    setType(type);
    setObjectType(Object::UnknownType);
}

Query::Query(const Query &other):
    d_ptr(other.d_ptr)
{
}

Query::~Query()
{
}

bool Query::operator==(const Query &other) const
{
    Q_D(const Query);
    return (d->id == other.id() && d->type == other.type());
}

bool Query::operator !=(const Query &other) const
{
    Q_D(const Query);
    return (d->id != other.id() || d->type != other.type());
}

bool Query::isValid() const
{
    Q_D(const Query);
    return (d->id != -1 && d->type != InvalidRequest
            && d->preprocessorData.operation() != InvalidOperation);
}

int Query::id() const
{
    Q_D(const Query);
    return d->id;
}

PreprocessorData Query::preprocessorData() const
{
    Q_D(const Query);
    return d->preprocessorData;
}

PreprocessorData & Query::preprocessorData()
{
    Q_D(Query);
    return d->preprocessorData;
}

RequestType Query::type() const
{
    Q_D(const Query);
    return d->type;
}

Object::ObjectType Query::objectType() const
{
    Q_D(const Query);
    return d->objectType;
}

void Query::setId(int id)
{
    Q_D(Query);
    d->id = id;
}

void Query::setPreprocessorData(const PreprocessorData &preprocessorData)
{
    Q_D(Query);
    d->preprocessorData = preprocessorData;
}

void Query::setType(RequestType type)
{
    Q_D(Query);
    d->type = type;
}

void Query::setObjectType(Object::ObjectType objectType)
{
    Q_D(Query);
    d->objectType = objectType;
}

}
