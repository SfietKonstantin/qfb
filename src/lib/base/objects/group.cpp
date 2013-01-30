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
 * @file group.cpp
 * @brief Implementation of QFB::Group
 */

#include "group.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"

namespace QFB
{

/**
 * @internal
 * @brief GROUP_VERSION_KEY
 */
static const char *GROUP_VERSION_KEY = "version";
/**
 * @internal
 * @brief GROUP_ICON_KEY
 */
static const char *GROUP_ICON_KEY = "icon";
/**
 * @internal
 * @brief GROUP_OWNER_KEY
 */
static const char *GROUP_OWNER_KEY = "owner";
/**
 * @internal
 * @brief GROUP_DESCRIPTION_KEY
 */
static const char *GROUP_DESCRIPTION_KEY = "description";
/**
 * @internal
 * @brief GROUP_LINK_KEY
 */
static const char *GROUP_LINK_KEY = "link";
/**
 * @internal
 * @brief GROUP_UPDATED_TIME_KEY
 */
static const char *GROUP_UPDATED_TIME_KEY = "updated_time";


/**
 * @internal
 * @short Private class for QFB::Group
 */
class GroupPrivate: public ObjectBasePrivate
{
public:
    /**
     * @internal
     * @short Default constructor
     */
    explicit GroupPrivate();
    /**
     * @internal
     * @short Owner
     */
    QFB::NamedObject * owner;
};

GroupPrivate::GroupPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

Group::Group(QObject *parent):
    NamedObject(parent)
{
}

Group::Group(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new GroupPrivate), parent)
{
    Q_D(Group);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create owner
    QVariantMap ownerData = d->propertiesMap.take(GROUP_OWNER_KEY).toMap();
    d->owner = createObject<QFB::NamedObject>(ownerData, this);
    // <<<<< custom object creation code
}

int Group::version() const
{
    Q_D(const Group);
    // >>>>> property version
    return d->propertiesMap.value(GROUP_VERSION_KEY).toString().toInt();
    // <<<<< property version
}

QUrl Group::icon() const
{
    Q_D(const Group);
    // >>>>> property icon
    return parseUrl(d->propertiesMap.value(GROUP_ICON_KEY).toString());
    // <<<<< property icon
}

QFB::NamedObject * Group::owner() const
{
    Q_D(const Group);
    // >>>>> property owner
    return d->owner;
    // <<<<< property owner
}

QString Group::description() const
{
    Q_D(const Group);
    // >>>>> property description
    return d->propertiesMap.value(GROUP_DESCRIPTION_KEY).toString();
    // <<<<< property description
}

QUrl Group::link() const
{
    Q_D(const Group);
    // >>>>> property link
    return parseUrl(d->propertiesMap.value(GROUP_LINK_KEY).toString());
    // <<<<< property link
}

QDateTime Group::updatedTime() const
{
    Q_D(const Group);
    // >>>>> property updated_time
    return d->propertiesMap.value(GROUP_UPDATED_TIME_KEY).toDateTime();
    // <<<<< property updated_time
}


// >>>>> custom source code
// <<<<< custom source code

}
