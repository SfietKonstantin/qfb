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

#include "post.h"
#include "object_p.h"

#include "userbase.h"

namespace QFB
{

Post::Post(QObject *parent) :
    Object(parent)
{
}

Post::Post(const PropertiesMap propertiesMap, QObject *parent):
    Object(parent)
{
    Q_D(Object);
    d->propertiesMap = propertiesMap;
}

UserBase * Post::from() const
{
    Q_D(const Object);
    return d->propertiesMap.value(FromProperty).value<UserBase *>();
}

QVariantList Post::toVariant() const
{
    Q_D(const Object);
    return d->propertiesMap.value(ToProperty).toList();
}

QList<UserBase *> Post::to() const
{
    Q_D(const Object);
    QVariantList toVariantList = d->propertiesMap.value(ToProperty).toList();
    QList<UserBase *> returned;
    foreach (QVariant toVariant, toVariantList) {
        returned.append(toVariant.value<UserBase *>());
    }
    return returned;
}

QString Post::message() const
{
    Q_D(const Object);
    return d->propertiesMap.value(MessageProperty).toString();
}

QUrl Post::picture() const
{
    Q_D(const Object);
    return d->propertiesMap.value(PictureProperty).toUrl();
}

QUrl Post::link() const
{
    Q_D(const Object);
    return d->propertiesMap.value(LinkProperty).toUrl();
}

QString Post::name() const
{
    Q_D(const Object);
    return d->propertiesMap.value(NameProperty).toString();
}

QString Post::caption() const
{
    Q_D(const Object);
    return d->propertiesMap.value(CaptionProperty).toString();
}

QString Post::description() const
{
    Q_D(const Object);
    return d->propertiesMap.value(DescriptionProperty).toString();
}

QUrl Post::source() const
{
    Q_D(const Object);
    return d->propertiesMap.value(SourceProperty).toUrl();
}

QUrl Post::icon() const
{
    Q_D(const Object);
    return d->propertiesMap.value(IconProperty).toUrl();
}

QString Post::type() const
{
    Q_D(const Object);
    return d->propertiesMap.value(TypeProperty).toString();
}

QString Post::story() const
{
    Q_D(const Object);
    return d->propertiesMap.value(StoryProperty).toString();
}

QString Post::objectId() const
{
    Q_D(const Object);
    return d->propertiesMap.value(ObjectIdProperty).toString();
}

QDateTime Post::createdTime() const
{
    Q_D(const Object);
    return d->propertiesMap.value(CreatedTimeProperty).toDateTime();
}

QDateTime Post::updatedTime() const
{
    Q_D(const Object);
    return d->propertiesMap.value(UpdatedTimeProperty).toDateTime();
}

}
