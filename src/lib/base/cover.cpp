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
 * @file cover.cpp
 * @brief Implementation of QFB::Cover
 */

#include "cover.h"
#include "object_p.h"
#include "cover_keys_p.h"

namespace QFB
{

Cover::Cover(QObject *parent) :
    Object(parent)
{
}

Cover::Cover(const PropertiesMap propertiesMap, QObject *parent):
    Object(propertiesMap, parent)
{
}

QUrl Cover::source() const
{
    Q_D(const Object);
    return d->propertiesMap.value(COVER_SOURCE_KEY).toUrl();
}

double Cover::offsetY() const
{
    Q_D(const Object);
    return d->propertiesMap.value(COVER_OFFSET_Y_KEY).toDouble();
}

}
