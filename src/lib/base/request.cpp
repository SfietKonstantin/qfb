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

#include "request.h"
#include "private/helper_p.h"

namespace QFB
{

Request::Request():
    d_ptr(new RequestPrivate)
{
    setId(-1);
    setType(InvalidRequest);
    setObjectType(Object::UnknownType);
}

Request::Request(int id, RequestType type):
    d_ptr(new RequestPrivate)
{
    setId(id);
    setType(type);
    setObjectType(Object::UnknownType);
}

Request::Request(const Request &other):
    d_ptr(other.d_ptr)
{
}

Request::~Request()
{
}

bool Request::operator==(const Request &other) const
{
    Q_D(const Request);
    return (d->id == other.id() && d->type == other.type());
}

bool Request::operator !=(const Request &other) const
{
    Q_D(const Request);
    return (d->id != other.id() || d->type != other.type());
}

bool Request::isValid() const
{
    Q_D(const Request);
    return (d->id != -1 && d->type != InvalidRequest
            && d->preprocessorData.operation() != InvalidOperation);
}

int Request::id() const
{
    Q_D(const Request);
    return d->id;
}

PreprocessorData Request::preprocessorData() const
{
    Q_D(const Request);
    return d->preprocessorData;
}

PreprocessorData & Request::preprocessorData()
{
    Q_D(Request);
    return d->preprocessorData;
}

RequestType Request::type() const
{
    Q_D(const Request);
    return d->type;
}

Object::ObjectType Request::objectType() const
{
    Q_D(const Request);
    return d->objectType;
}

void Request::setId(int id)
{
    Q_D(Request);
    d->id = id;
}

void Request::setPreprocessorData(const PreprocessorData &preprocessorData)
{
    Q_D(Request);
    d->preprocessorData = preprocessorData;
}

void Request::setType(RequestType type)
{
    Q_D(Request);
    d->type = type;
}

void Request::setObjectType(Object::ObjectType objectType)
{
    Q_D(Request);
    d->objectType = objectType;
}

}
