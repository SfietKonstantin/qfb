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
 * @file photolistprocessor.cpp
 * @brief Implementation of QFB::PhotoListProcessor
 */

#include "photolistprocessor.h"
#include <QtCore/QCoreApplication>
#include "abstractpagingprocessor_p.h"
#include "photo.h"
#include "photoprocessor_p.h"
#include "helper_p.h"
#include "jsonhelper_p.h"
#include "paging_keys_p.h"

namespace QFB
{

/**
 * @internal
 * @brief DATA_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *DATA_KEY = "data";

/**
 * @internal
 * @brief Private class for QFB::PhotoListProcessor
 */
class PhotoListProcessorPrivate: public AbstractPagingProcessorPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit PhotoListProcessorPrivate();
    /**
     * @internal
     * @brief Photo list
     */
    QList<Photo *> photoList;
};

PhotoListProcessorPrivate::PhotoListProcessorPrivate():
    AbstractPagingProcessorPrivate()
{
}

////// End of private class //////

PhotoListProcessor::PhotoListProcessor(QObject *parent):
    AbstractPagingProcessor(*(new PhotoListProcessorPrivate), parent)
{
}

QList<Photo *> PhotoListProcessor::photoList() const
{
    Q_D(const PhotoListProcessor);
    return d->photoList;
}

bool PhotoListProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(PhotoListProcessor);
    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);

    if (!rootObject.contains(DATA_KEY)) {
        setError("Received data do not contains correct data.");
        return false;
    }

    JsonArray dataArray = QFB_JSON_GET_ARRAY(rootObject.value(DATA_KEY));

    foreach (JsonValue value, dataArray) {
        if (QFB_JSON_IS_OBJECT(value)) {
            JsonObject object = QFB_JSON_GET_OBJECT(value);
            Photo * photo = PhotoProcessorPrivate::createPhoto(object);
            if (photo) {
                d->photoList.append(photo);
            }
        }
    }

    JsonObject pagingObject = QFB_JSON_GET_OBJECT(rootObject.value(PAGING_KEY));
    QUrl nextPageUrl = parseUrl(pagingObject.value(PAGING_NEXT_KEY).toString());
    setNextPageUrl(nextPageUrl);

    return true;
}

}
