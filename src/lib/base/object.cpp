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
 * @file object.cpp
 * @brief Implementation of QFB::Object
 */

#include "object.h"
#include "objectbase_p.h"
#include "object_keys_p.h"
#include "object_type_keys_p.h"

namespace QFB
{

Object::Object(QObject *parent):
    ObjectBase(parent)
{
}

Object::Object(const PropertiesMap &propertiesMap, QObject *parent):
    ObjectBase(propertiesMap, parent)
{
    Q_D(ObjectBase);
    d->propertiesMap = propertiesMap;
    if (!propertiesMap.contains(OBJECT_TYPE_KEY)) {
        d->propertiesMap.insert(OBJECT_TYPE_KEY, Object::Unknown);
    }
}

Object::Object(ObjectBasePrivate &dd, QObject *parent):
    ObjectBase(dd, parent)
{
}

QString Object::facebookId() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(OBJECT_ID_KEY).toString();
}

Object::ObjectType Object::objectType() const
{
    Q_D(const ObjectBase);
    return (Object::ObjectType) d->propertiesMap.value(OBJECT_TYPE_KEY).toInt();
}

}
