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

#include "feedprocessor.h"
#include "abstractpagingprocessor_p.h"
#include <QtCore/QCoreApplication>
#include "helper_p.h"
#include "jsonhelper_p.h"
#include "namedobject.h"
#include "namedobject_keys_p.h"
#include "object_keys_p.h"
#include "paging_keys_p.h"
#include "post.h"
#include "post_keys_p.h"
#include "processorhelper_p.h"

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
 * @brief TO_KEY
 */
static const char *TO_DATA_KEY = "data";

class FeedProcessorPrivate: public AbstractPagingProcessorPrivate
{
public:
    explicit FeedProcessorPrivate();
    /**
     * @internal
     * @brief Friend list
     */
    QList<Post *> feed;
};

FeedProcessorPrivate::FeedProcessorPrivate():
    AbstractPagingProcessorPrivate()
{
}

FeedProcessor::FeedProcessor(QObject *parent):
    AbstractPagingProcessor(*(new FeedProcessorPrivate()), parent)
{
}

QList<Post *> FeedProcessor::feed() const
{
    Q_D(const FeedProcessor);
    return d->feed;
}

bool FeedProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(FeedProcessor);

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
            PropertiesMap propertiesMap;

            propertiesMap.insert(OBJECT_ID_KEY, object.value(OBJECT_ID_KEY).toString());
            propertiesMap.insert(POST_FROM_KEY,
                               createNamedObject(QFB_JSON_GET_OBJECT(object.value(POST_FROM_KEY))));

            JsonObject toParentObject = QFB_JSON_GET_OBJECT(object.value(POST_TO_KEY));
            JsonArray toArray = QFB_JSON_GET_ARRAY(toParentObject.value(TO_DATA_KEY));
            QVariantList toList;
            foreach (JsonValue toValue, toArray) {
                JsonObject toObject = QFB_JSON_GET_OBJECT(toValue);
                toList.append(createNamedObject(toObject));
            }
            propertiesMap.insert(POST_TO_KEY, toList);

            propertiesMap.insert(POST_MESSAGE_KEY, object.value(POST_MESSAGE_KEY).toString());
            propertiesMap.insert(POST_PICTURE_KEY,
                                 parseUrl(object.value(POST_PICTURE_KEY).toString()));
            propertiesMap.insert(POST_LINK_KEY, parseUrl(object.value(POST_LINK_KEY).toString()));
            propertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                                 object.value(NAMEDOBJECT_NAME_KEY).toString());
            propertiesMap.insert(POST_CAPTION_KEY, object.value(POST_CAPTION_KEY).toString());
            propertiesMap.insert(POST_DESCRIPTION_KEY,
                                 object.value(POST_DESCRIPTION_KEY).toString());
            propertiesMap.insert(POST_SOURCE_KEY,
                                 parseUrl(object.value(POST_SOURCE_KEY).toString()));
            propertiesMap.insert(POST_ICON_KEY,
                                 parseUrl(object.value(POST_ICON_KEY).toString()));
            propertiesMap.insert(POST_TYPE_KEY, object.value(POST_TYPE_KEY).toString());
            propertiesMap.insert(POST_STORY_KEY, object.value(POST_STORY_KEY).toString());
            propertiesMap.insert(POST_OBJECT_ID_KEY,
                                 object.value(POST_OBJECT_ID_KEY).toString());
            QDateTime createdTime
                    = QDateTime::fromString(object.value(POST_CREATED_TIME_KEY).toString(),
                                            Qt::ISODate);
            propertiesMap.insert(POST_CREATED_TIME_KEY, createdTime);
            QDateTime updatedTime
                    = QDateTime::fromString(object.value(POST_UPDATED_TIME_KEY).toString(),
                                            Qt::ISODate);
            propertiesMap.insert(POST_UPDATED_TIME_KEY, updatedTime);

            Post *post = new Post(propertiesMap);
            post->moveToThread(QCoreApplication::instance()->thread());
            d->feed.append(post);
        }
    }

    JsonObject pagingObject = QFB_JSON_GET_OBJECT(rootObject.value(PAGING_KEY));
    QUrl nextPageUrl = parseUrl(pagingObject.value(PAGING_NEXT_KEY).toString());
    setNextPageUrl(nextPageUrl);

    return true;
}

}
