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

#include "writablequery_p.h"

namespace QFB
{

WritableQuery::WritableQuery():
    Query(*(new WritableQueryPrivate))
{
}

WritableQuery::WritableQuery(int id, RequestType type):
    Query(*(new WritableQueryPrivate))
{
    Q_D(Query);
    d->id = id;
    d->type = type;
    d->objectType = Object::UnknownType;
}

WritableQuery::WritableQuery(const WritableQuery &other):
    Query(*other.d_ptr.data())
{
}

WritableQuery::WritableQuery(const Query &query):
    Query(query)
{
}

WritableQuery WritableQuery::createWritableQuery(const Query &query)
{
    return WritableQuery(query);
}

PreprocessorData WritableQuery::preprocessorData() const
{
    Q_D(const WritableQuery);
    return d->preprocessorData;
}

PreprocessorData & WritableQuery::preprocessorData()
{
    Q_D(WritableQuery);
    return d->preprocessorData;
}

void WritableQuery::setId(int id)
{
    Q_D(WritableQuery);
    d->id = id;
}

void WritableQuery::setType(RequestType type)
{
    Q_D(WritableQuery);
    d->type = type;
}

void WritableQuery::setObjectType(Object::ObjectType objectType)
{
    Q_D(WritableQuery);
    d->objectType = objectType;
}

}
