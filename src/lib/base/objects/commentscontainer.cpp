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
 * @file commentscontainer.cpp
 * @brief Implementation of QFB::CommentsContainer
 */

#include "commentscontainer.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"
#include "private/commentscontainer_keys_p.h"

namespace QFB
{

/**
 * @internal
 * @short Private class for QFB::CommentsContainer
 */
class CommentsContainerPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit CommentsContainerPrivate();
    /**
     * @internal
     * @short List of data
     */
    QList<QFB::Comment *> data;
};

CommentsContainerPrivate::CommentsContainerPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

CommentsContainer::CommentsContainer(QObject *parent):
    ObjectBase(parent)
{
}

CommentsContainer::CommentsContainer(const QVariantMap propertiesMap, QObject *parent):
    ObjectBase(*(new CommentsContainerPrivate), parent)
{
    Q_D(CommentsContainer);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create data
    QVariantList dataData = d->propertiesMap.take(COMMENTSCONTAINER_DATA_KEY).toList();
    d->data = createList<QFB::Comment>(dataData, this);
    // <<<<< custom object creation code
}

int CommentsContainer::count() const
{
    Q_D(const CommentsContainer);
    // >>>>> property count
    return d->propertiesMap.value(COMMENTSCONTAINER_COUNT_KEY).toString().toInt();
    // <<<<< property count
}

QList<QFB::Comment *> CommentsContainer::data() const
{
    Q_D(const CommentsContainer);
    // >>>>> property data
    return d->data;
    // <<<<< property data
}


// >>>>> custom source code
// <<<<< custom source code

}
