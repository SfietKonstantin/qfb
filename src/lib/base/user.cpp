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

#include "user.h"
#include "object_p.h"

namespace QFB
{

User::User(QObject *parent) :
    UserBase(parent)
{
}

User::User(const PropertiesMap propertiesMap, QObject *parent):
    UserBase(parent)
{
    Q_D(Object);
    d->propertiesMap = propertiesMap;
}

QString User::firstName() const
{
    Q_D(const Object);
    return d->propertiesMap.value(FirstName).toString();
}

QString User::middleName() const
{
    Q_D(const Object);
    return d->propertiesMap.value(MiddleName).toString();
}

QString User::lastName() const
{
    Q_D(const Object);
    return d->propertiesMap.value(LastName).toString();
}

QString User::gender() const
{
    Q_D(const Object);
    return d->propertiesMap.value(Gender).toString();
}

QString User::locale() const
{
    Q_D(const Object);
    return d->propertiesMap.value(Locale).toString();
}

QString User::link() const
{
    Q_D(const Object);
    return d->propertiesMap.value(Link).toString();
}

QString User::username() const
{
    Q_D(const Object);
    return d->propertiesMap.value(Username).toString();
}

QString User::bio() const
{
    Q_D(const Object);
    return d->propertiesMap.value(Bio).toString();
}

QDate User::birthday() const
{
    Q_D(const Object);
    return d->propertiesMap.value(Birthday).toDate();
}

}
