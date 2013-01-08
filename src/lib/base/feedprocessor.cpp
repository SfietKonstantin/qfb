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
#include "post.h"

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
 * @brief FROM_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *FROM_KEY = "from";
/**
 * @internal
 * @brief ID_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *ID_KEY = "id";
/**
 * @internal
 * @brief NAME_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *NAME_KEY = "name";
/**
 * @internal
 * @brief TO_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *TO_KEY = "to";
/**
 * @internal
 * @brief TO_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *TO_DATA_KEY = "data";
/**
 * @internal
 * @brief MESSAGE_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *MESSAGE_KEY = "message";
/**
 * @internal
 * @brief PICTURE_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *PICTURE_KEY = "picture";
/**
 * @internal
 * @brief LINK_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *LINK_KEY = "link";
/**
 * @internal
 * @brief CAPTION_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *CAPTION_KEY = "caption";
/**
 * @internal
 * @brief DESCRIPTION_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *DESCRIPTION_KEY = "description";
/**
 * @internal
 * @brief SOURCE_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *SOURCE_KEY = "source";
/**
 * @internal
 * @brief ICON_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *ICON_KEY = "icon";
/**
 * @internal
 * @brief TYPE_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *TYPE_KEY = "type";
/**
 * @internal
 * @brief STORY_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *STORY_KEY = "story";
/**
 * @internal
 * @brief OBJECT_ID_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *OBJECT_ID_KEY = "object_id";
/**
 * @internal
 * @brief CREATED_TIME_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *CREATED_TIME_KEY = "created_time";
/**
 * @internal
 * @brief UPDATED_TIME_KEY
 *
 * Used in QFB::FeedReply.
 */
static const char *UPDATED_TIME_KEY = "updated_time";
/**
 * @internal
 * @brief PAGING_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *PAGING_KEY = "paging";
/**
 * @internal
 * @brief PAGING_NEXT_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *PAGING_NEXT_KEY = "next";

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

            propertiesMap.insert(IdProperty, object.value(ID_KEY).toString());

            PropertiesMap fromPropertiesMap;
            JsonObject fromObject = QFB_JSON_GET_OBJECT(object.value(FROM_KEY));
            fromPropertiesMap.insert(IdProperty, fromObject.value(ID_KEY).toString());
            fromPropertiesMap.insert(NameProperty, fromObject.value(NAME_KEY).toString());
            propertiesMap.insert(FromProperty,
                                 QVariant::fromValue(new NamedObject(fromPropertiesMap)));

            JsonObject toParentObject = QFB_JSON_GET_OBJECT(object.value(TO_KEY));
            JsonArray toArray = QFB_JSON_GET_ARRAY(toParentObject.value(TO_DATA_KEY));
            QVariantList toList;
            foreach (JsonValue toValue, toArray) {
                JsonObject toObject = QFB_JSON_GET_OBJECT(toValue);
                PropertiesMap toPropertiesMap;
                toPropertiesMap.insert(IdProperty, toObject.value(ID_KEY).toString());
                toPropertiesMap.insert(NameProperty, toObject.value(NAME_KEY).toString());
                toList.append(QVariant::fromValue(new NamedObject(toPropertiesMap)));
            }
            propertiesMap.insert(ToProperty, toList);

            propertiesMap.insert(MessageProperty, object.value(MESSAGE_KEY).toString());
            propertiesMap.insert(PictureProperty, parseUrl(object.value(PICTURE_KEY).toString()));
            propertiesMap.insert(LinkProperty, parseUrl(object.value(LINK_KEY).toString()));
            propertiesMap.insert(NameProperty, object.value(NAME_KEY).toString());
            propertiesMap.insert(CaptionProperty, object.value(CAPTION_KEY).toString());
            propertiesMap.insert(DescriptionProperty, object.value(DESCRIPTION_KEY).toString());
            propertiesMap.insert(SourceProperty, parseUrl(object.value(SOURCE_KEY).toString()));
            propertiesMap.insert(IconProperty, parseUrl(object.value(ICON_KEY).toString()));
            propertiesMap.insert(TypeProperty, object.value(TYPE_KEY).toString());
            propertiesMap.insert(StoryProperty, object.value(STORY_KEY).toString());
            propertiesMap.insert(ObjectIdProperty, object.value(OBJECT_ID_KEY).toString());
            QDateTime createdTime = QDateTime::fromString(object.value(CREATED_TIME_KEY).toString(),
                                                          Qt::ISODate);
            propertiesMap.insert(CreatedTimeProperty, createdTime);
            QDateTime updatedTime = QDateTime::fromString(object.value(UPDATED_TIME_KEY).toString(),
                                                          Qt::ISODate);
            propertiesMap.insert(UpdatedTimeProperty, updatedTime);

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
