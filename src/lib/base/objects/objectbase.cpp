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
 * @file objectbase.cpp
 * @brief Implementation of QFB::ObjectBase
 */


#include "objectbase.h"
#include "private/objectbase_p.h"

namespace QFB
{

ObjectBasePrivate::ObjectBasePrivate()
{
}

////// End of private class ///////

ObjectBase::ObjectBase(QObject *parent) :
    QObject(parent), d_ptr(new ObjectBasePrivate())
{
}

ObjectBase::ObjectBase(const PropertiesMap &propertiesMap, QObject *parent):
    QObject(parent), d_ptr(new ObjectBasePrivate())
{
    Q_D(ObjectBase);
    d->propertiesMap = propertiesMap;
}

ObjectBase::ObjectBase(ObjectBasePrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

ObjectBase::~ObjectBase()
{
}

}
