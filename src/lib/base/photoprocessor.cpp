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
 * @file photoprocessor.cpp
 * @brief Implementation of QFB::PhotoProcessor
 */

#include "photoprocessor.h"
#include "photoprocessor_p.h"
#include <QtCore/QCoreApplication>
#include "photo.h"
#include "photo_keys_p.h"
#include "helper_p.h"
#include "namedobject_keys_p.h"
#include "object_keys_p.h"
#include "processorhelper_p.h"

namespace QFB
{

PhotoProcessorPrivate::PhotoProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    photo = 0;
}

Photo * PhotoProcessorPrivate::createPhoto(const JsonObject &jsonObject)
{
    PropertiesMap propertiesMap;
    propertiesMap.insert(OBJECT_ID_KEY, jsonObject.value(OBJECT_ID_KEY).toString());
    propertiesMap.insert(PHOTO_FROM_KEY,
                         createNamedObject(QFB_JSON_GET_OBJECT(jsonObject.value(PHOTO_FROM_KEY))));
    propertiesMap.insert(NAMEDOBJECT_NAME_KEY, jsonObject.value(NAMEDOBJECT_NAME_KEY).toString());
    propertiesMap.insert(PHOTO_ICON_KEY, jsonObject.value(PHOTO_ICON_KEY).toString());
    propertiesMap.insert(PHOTO_PICTURE_KEY, jsonObject.value(PHOTO_PICTURE_KEY).toString());
    propertiesMap.insert(PHOTO_SOURCE_KEY, parseUrl(jsonObject.value(PHOTO_SOURCE_KEY).toString()));
    propertiesMap.insert(PHOTO_HEIGHT_KEY, (int) jsonObject.value(PHOTO_HEIGHT_KEY).toDouble());
    propertiesMap.insert(PHOTO_WIDTH_KEY, (int) jsonObject.value(PHOTO_WIDTH_KEY).toDouble());
    propertiesMap.insert(PHOTO_LINK_KEY, parseUrl(jsonObject.value(PHOTO_LINK_KEY).toString()));
    Photo *photo = new Photo(propertiesMap);
    photo->moveToThread(QCoreApplication::instance()->thread());
    return photo;
}
////// End of private class //////

PhotoProcessor::PhotoProcessor(QObject *parent):
    AbstractGraphProcessor(*(new PhotoProcessorPrivate), parent)
{
}

Photo * PhotoProcessor::photo() const
{
    Q_D(const PhotoProcessor);
    return d->photo;
}

bool PhotoProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(PhotoProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);
    d->photo = d->createPhoto(rootObject);
    if (d->photo) {
        return true;
    } else {
        return false;
    }
}

}
