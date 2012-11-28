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
#include "object_p.h"

namespace QFB
{

ObjectPrivate::ObjectPrivate(Object *q):
    q_ptr(q)
{
}

////// End of private class //////

Object::Object(QObject *parent):
    QObject(parent), d_ptr(new ObjectPrivate(this))
{
}

Object::Object(const QString &id, QObject *parent):
    QObject(parent), d_ptr(new ObjectPrivate(this))
{
    Q_D(Object);
    d->id = id;
}

Object::Object(ObjectPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

Object::~Object()
{
}

QString Object::id() const
{
    Q_D(const Object);
    return d->id;
}

}
