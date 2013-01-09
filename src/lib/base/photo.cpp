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
 * @file photo.cpp
 * @brief Implementation of QFB::Photo
 */

#include "photo.h"
#include "objectbase_p.h"
#include "photo_keys_p.h"

#include "namedobject_keys_p.h"

#include "object_keys_p.h"

namespace QFB
{

Photo::Photo(QObject *parent):
    NamedObject(parent)
{
}

Photo::Photo(const PropertiesMap propertiesMap, QObject *parent):
    NamedObject(propertiesMap, parent)
{
    Q_D(ObjectBase);

    // Reparent from
    QObject *fromObject = d->propertiesMap.value(PHOTO_FROM_KEY).value<NamedObject *>();
    if (fromObject) {
        fromObject->setParent(this);
    }

}
QString Photo::id() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(OBJECT_ID_KEY).toString();
}

NamedObject * Photo::from() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_FROM_KEY).value<NamedObject *>();
}

QString Photo::name() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(NAMEDOBJECT_NAME_KEY).toString();
}

QString Photo::icon() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_ICON_KEY).toString();
}

QString Photo::picture() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_PICTURE_KEY).toString();
}

QUrl Photo::source() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_SOURCE_KEY).toUrl();
}

int Photo::height() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_HEIGHT_KEY).toInt();
}

int Photo::width() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_WIDTH_KEY).toInt();
}

QUrl Photo::link() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(PHOTO_LINK_KEY).toUrl();
}

}
