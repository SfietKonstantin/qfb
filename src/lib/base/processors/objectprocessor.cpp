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

#include "objectprocessor.h"
#include "private/objectprocessor_p.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include "private/abstractgraphprocessor_p.h"
#include "private/helper_p.h"
#include "private/jsonhelper_p.h"
// All object types
#include "objects/object.h"
#include "objects/album.h"
#include "objects/photo.h"
#include "objects/comment.h"
#include "objects/post.h"
#include "objects/user.h"

namespace QFB
{

ObjectProcessorPrivate::ObjectProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    object = 0;
}

QVariantMap ObjectProcessorPrivate::createObjectProperties(const JsonObject &object)
{
    QVariantMap data;
    foreach (QString key, object.keys()) {
        JsonValue value = object.value(key);
        if (QFB_JSON_IS_BOOL(value)) {
            data.insert(key, QFB_JSON_GET_BOOL(value));
        } else if (QFB_JSON_IS_DOUBLE(value)) {
            data.insert(key, QFB_JSON_GET_DOUBLE(value));
        } else if (QFB_JSON_IS_OBJECT(value)) {
            data.insert(key, createObjectProperties(QFB_JSON_GET_OBJECT(value)));
        } else if (QFB_JSON_IS_STRING(value)) {
            QString valueString = QFB_JSON_GET_STRING(value);
            if (key.contains("time")) {
                QDateTime valueDateTime = QDateTime::fromString(valueString, Qt::ISODate);
                data.insert(key, valueDateTime);
            } else {
                data.insert(key, valueString);
            }
        } else if (QFB_JSON_IS_ARRAY(value)) {
            JsonArray array = QFB_JSON_GET_ARRAY(value);
            if (array.isEmpty()) {
                data.insert(key, QList<QVariant>());
            } else {
                JsonValue first = array.first();
                QVariantList variantArray;
                if (QFB_JSON_IS_OBJECT(first)) {
                    foreach (JsonValue arrayValue, array) {
                        variantArray.append(createObjectProperties(QFB_JSON_GET_OBJECT(arrayValue)));
                    }
                } else if (QFB_JSON_IS_STRING(first)) {
                    foreach (JsonValue arrayValue, array) {
                        variantArray.append(QFB_JSON_GET_STRING(arrayValue));
                    }
                } else {
                    qWarning() << "Value stored in" << key << "is an array of unknown type.";
                }
                data.insert(key, variantArray);
            }
        }
    }
    return data;
}

Object * ObjectProcessorPrivate::guessType(const QVariantMap &propertiesMap, QObject *parent)
{
    if (propertiesMap.keys().size() == 2 && propertiesMap.keys().contains("id")
        && propertiesMap.keys().contains("name")) {
        return new NamedObject(propertiesMap, parent);
    } else if (propertiesMap.keys().size() == 1 && propertiesMap.keys().contains("id")) {
        return new Object(propertiesMap, parent);
    } else {
        return 0;
    }
}

Object * ObjectProcessorPrivate::createObject(const JsonObject &jsonObject, const Query &query,
                                              QObject *parent)
{
    Object *object = 0;
    QVariantMap propertiesMap = ObjectProcessorPrivate::createObjectProperties(jsonObject);

    switch (query.objectType()) {
    case Object::AlbumType:
        object = new Album(propertiesMap, parent);
        break;
    case Object::PhotoType:
        object = new Photo(propertiesMap, parent);
        break;
    case Object::PostType:
        object = new Post(propertiesMap, parent);
        break;
    case Object::CommentType:
        object = new Comment(propertiesMap, parent);
        break;
    case Object::UserType:
        object = new User(propertiesMap, parent);
        break;
    default:
        object = ObjectProcessorPrivate::guessType(propertiesMap, parent);
        break;
    }
    return object;
}

////// End of private class //////

ObjectProcessor::ObjectProcessor(QObject *parent):
    AbstractGraphProcessor(*(new ObjectProcessorPrivate), parent)
{
}

ObjectProcessor::ObjectProcessor(AbstractGraphProcessorPrivate &dd, QObject *parent):
    AbstractGraphProcessor(dd, parent)
{
}

Object * ObjectProcessor::object() const
{
    Q_D(const ObjectProcessor);
    return d->object;
}

bool ObjectProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(ObjectProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);

    d->object = d->createObject(rootObject, query());

    if (d->object) {
        d->object->moveToThread(QCoreApplication::instance()->thread());
    }

    return true;
}

}
