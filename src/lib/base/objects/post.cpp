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
 * @file post.cpp
 * @brief Implementation of QFB::Post
 */

#include "post.h"
#include "private/objectbase_p.h"
#include "private/post_keys_p.h"

namespace QFB
{

Post::Post(QObject *parent) :
    NamedObject(parent)
{
}

Post::Post(const PropertiesMap propertiesMap, QObject *parent):
    NamedObject(propertiesMap, parent)
{
    Q_D(ObjectBase);
    // Reparent from
    QObject *fromObject = d->propertiesMap.value(POST_FROM_KEY).value<NamedObject *>();
    if (fromObject) {
        fromObject->setParent(this);
    }

    // Reparent to
    QVariantList toVariantList = d->propertiesMap.value(POST_TO_KEY).toList();
    foreach (QVariant toVariant, toVariantList) {
        QObject *to = toVariant.value<NamedObject *>();
        to->setParent(this);
    }

}

NamedObject * Post::from() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_FROM_KEY).value<NamedObject *>();
}

QVariantList Post::toVariant() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_TO_KEY).toList();
}

QList<NamedObject *> Post::to() const
{
    Q_D(const ObjectBase);
    QVariantList toVariantList = d->propertiesMap.value(POST_TO_KEY).toList();
    QList<NamedObject *> returned;
    foreach (QVariant toVariant, toVariantList) {
        returned.append(toVariant.value<NamedObject *>());
    }
    return returned;
}

QString Post::message() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_MESSAGE_KEY).toString();
}

QUrl Post::picture() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_PICTURE_KEY).toUrl();
}

QUrl Post::link() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_LINK_KEY).toUrl();
}

QString Post::caption() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_CAPTION_KEY).toString();
}

QString Post::description() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_DESCRIPTION_KEY).toString();
}

QUrl Post::source() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_SOURCE_KEY).toUrl();
}

QUrl Post::icon() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_ICON_KEY).toUrl();
}

QString Post::type() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_TYPE_KEY).toString();
}

QString Post::story() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_STORY_KEY).toString();
}

QString Post::objectId() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_OBJECT_ID_KEY).toString();
}

QDateTime Post::createdTime() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_CREATED_TIME_KEY).toDateTime();
}

QDateTime Post::updatedTime() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(POST_UPDATED_TIME_KEY).toDateTime();
}

}
