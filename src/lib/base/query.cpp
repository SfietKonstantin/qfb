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
#include "private/preprocessordata_p.h"

namespace QFB
{

Query::Query():
    d_ptr(new QueryPrivate)
{
    Q_D(Query);
    d->id = -1;
    d->type = InvalidRequest;
    d->objectType = Object::UnknownType;
}

Query::Query(const Query &other):
    d_ptr(other.d_ptr)
{
}

Query::Query(QueryPrivate &dd):
    d_ptr(&dd)
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
    return (d->id != -1 && d->type != InvalidRequest);
}

int Query::id() const
{
    Q_D(const Query);
    return d->id;
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

}
