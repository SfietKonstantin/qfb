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
 * @file albumlistprocessor.cpp
 * @brief Implementation of QFB::AlbumListProcessor
 */

#include "albumlistprocessor.h"
#include <QtCore/QCoreApplication>
#include "private/abstractpagingprocessor_p.h"
#include "private/albumprocessor_p.h"
#include "private/helper_p.h"
#include "private/jsonhelper_p.h"
#include "private/paging_keys_p.h"
#include "objects/album.h"

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
 * @brief Private class for QFB::AlbumListProcessor
 */
class AlbumListProcessorPrivate: public AbstractPagingProcessorPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit AlbumListProcessorPrivate();
    /**
     * @internal
     * @brief Album list
     */
    QList<Album *> albumList;
};

AlbumListProcessorPrivate::AlbumListProcessorPrivate():
    AbstractPagingProcessorPrivate()
{
}

////// End of private class //////

AlbumListProcessor::AlbumListProcessor(QObject *parent):
    AbstractPagingProcessor(*(new AlbumListProcessorPrivate), parent)
{
}

QList<Album *> AlbumListProcessor::albumList() const
{
    Q_D(const AlbumListProcessor);
    return d->albumList;
}

bool AlbumListProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(AlbumListProcessor);
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
            Album * album = AlbumProcessorPrivate::createAlbum(object);
            if (album) {
                d->albumList.append(album);
            }
        }
    }

    JsonObject pagingObject = QFB_JSON_GET_OBJECT(rootObject.value(PAGING_KEY));
    QUrl nextPageUrl = parseUrl(pagingObject.value(PAGING_NEXT_KEY).toString());
    setNextPageUrl(nextPageUrl);

    return true;
}

}