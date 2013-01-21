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

/**
 * @file cover.cpp
 * @brief Implementation of QFB::Cover
 */

#include "cover.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"
#include "private/cover_keys_p.h"

namespace QFB
{

/**
 * @internal
 * @short Private class for QFB::Cover
 */
class CoverPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit CoverPrivate();
};

CoverPrivate::CoverPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

Cover::Cover(QObject *parent):
    ObjectBase(parent)
{
}

Cover::Cover(const QVariantMap propertiesMap, QObject *parent):
    ObjectBase(*(new CoverPrivate), parent)
{
    Q_D(Cover);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // <<<<< custom object creation code
}

QUrl Cover::source() const
{
    Q_D(const Cover);
    // >>>>> property source
    return parseUrl(d->propertiesMap.value(COVER_SOURCE_KEY).toString());
    // <<<<< property source
}

double Cover::offsetY() const
{
    Q_D(const Cover);
    // >>>>> property offset_y
    return d->propertiesMap.value(COVER_OFFSET_Y_KEY).toDouble();
    // <<<<< property offset_y
}


// >>>>> custom source code
// <<<<< custom source code

}
