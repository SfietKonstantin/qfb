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
 * @file likescontainer.cpp
 * @brief Implementation of QFB::LikesContainer
 */

#include "likescontainer.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief LIKESCONTAINER_COUNT_KEY
 */
static const char *LIKESCONTAINER_COUNT_KEY = "count";
/**
 * @internal
 * @brief LIKESCONTAINER_DATA_KEY
 */
static const char *LIKESCONTAINER_DATA_KEY = "data";


/**
 * @internal
 * @short Private class for QFB::LikesContainer
 */
class LikesContainerPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit LikesContainerPrivate();
    /**
     * @internal
     * @short List of data
     */
    QList<QFB::NamedObject *> data;
};

LikesContainerPrivate::LikesContainerPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

LikesContainer::LikesContainer(QObject *parent):
    ObjectBase(parent)
{
}

LikesContainer::LikesContainer(const QVariantMap propertiesMap, QObject *parent):
    ObjectBase(*(new LikesContainerPrivate), parent)
{
    Q_D(LikesContainer);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create data
    QVariantList dataData = d->propertiesMap.take(LIKESCONTAINER_DATA_KEY).toList();
    d->data = createList<QFB::NamedObject>(dataData, this);
    // <<<<< custom object creation code
}

int LikesContainer::count() const
{
    Q_D(const LikesContainer);
    // >>>>> property count
    return d->propertiesMap.value(LIKESCONTAINER_COUNT_KEY).toString().toInt();
    // <<<<< property count
}

QList<QFB::NamedObject *> LikesContainer::data() const
{
    Q_D(const LikesContainer);
    // >>>>> property data
    return d->data;
    // <<<<< property data
}


// >>>>> custom source code
// <<<<< custom source code

}
