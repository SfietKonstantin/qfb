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
 * @file friendbase.cpp
 * @brief Implementation of QFB::FriendBase
 */

#include "friendbase.h"
#include "friendbase_p.h"

namespace QFB
{

FriendBasePrivate::FriendBasePrivate(FriendBase *q):
    ObjectPrivate(q)
{
}

////// End of private class //////

FriendBase::FriendBase(QObject *parent) :
    Object(*(new FriendBasePrivate(this)), parent)
{
}

FriendBase::FriendBase(const QString &id, const QString &name, QObject *parent):
    Object(*(new FriendBasePrivate(this)), parent)
{
    Q_D(FriendBase);
    d->id = id;
    d->name = name;
}

FriendBase::FriendBase(FriendBasePrivate &dd, QObject *parent):
    Object(dd, parent)
{
}

QString FriendBase::name() const
{
    Q_D(const FriendBase);
    return d->name;
}

}
