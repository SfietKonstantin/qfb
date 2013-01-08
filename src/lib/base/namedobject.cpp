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
 * @file namedobject.cpp
 * @brief Implementation of QFB::NamedObject
 */

#include "namedobject.h"
#include "objectbase_p.h"
#include "namedobject_keys_p.h"

namespace QFB
{

NamedObject::NamedObject(QObject *parent) :
    Object(parent)
{
}

NamedObject::NamedObject(const PropertiesMap propertiesMap, QObject *parent):
    Object(propertiesMap, parent)
{
}

QString NamedObject::name() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(NAMEDOBJECT_NAME_KEY).toString();
}

}
