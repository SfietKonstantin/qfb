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

#include "status.h"
#include "object_p.h"

#include "userbase.h"

namespace QFB
{

Status::Status(QObject *parent) :
    Object(parent)
{
}

Status::Status(const PropertiesMap propertiesMap, QObject *parent):
    Object(parent)
{
    Q_D(Object);
    d->propertiesMap = propertiesMap;
}

UserBase * Status::from() const
{
    Q_D(const Object);
    return d->propertiesMap.value(FromProperty).value<UserBase *>();
}

QString Status::message() const
{
    Q_D(const Object);
    return d->propertiesMap.value(MessageProperty).toString();
}

QDateTime Status::updatedTime() const
{
    Q_D(const Object);
    return d->propertiesMap.value(UpdatedTimeProperty).toDateTime();
}

}
