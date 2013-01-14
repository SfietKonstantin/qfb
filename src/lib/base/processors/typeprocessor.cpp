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

#include "typeprocessor.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include "private/abstractgraphprocessor_p.h"
#include "private/helper_p.h"
#include "private/jsonhelper_p.h"
#include "objects/object.h"
#include "private/object_keys_p.h"
#include "private/object_type_keys_p.h"

namespace QFB
{

/**
 * @internal
 * @brief METADATA_KEY
 *
 * Used in QFB::TypeProcessor.
 */
static const char *METADATA_KEY = "metadata";
/**
 * @internal
 * @brief METADATA_REQUEST_VALUE
 *
 * Used in QFB::TypeProcessor.
 */
static const char *METADATA_REQUEST_VALUE = "1";
/**
 * @internal
 * @brief FIELDS_KEY
 *
 * Used in QFB::TypeProcessor.
 */
static const char *FIELDS_KEY = "fields";
/**
 * @internal
 * @brief METADATA_TYPE_VALUE
 *
 * Used in QFB::TypeProcessor.
 */
static const char *METADATA_TYPE_VALUE = "type";
/**
 * @internal
 * @brief ACHIEVEMENT
 *
 * Used in QFB::TypeProcessor.
 */
static const char *ACHIEVEMENT = "achievement";
/**
 * @internal
 * @brief ALBUM
 *
 * Used in QFB::TypeProcessor.
 */
static const char *ALBUM = "album";
/**
 * @internal
 * @brief APPLICATION
 *
 * Used in QFB::TypeProcessor.
 */
static const char *APPLICATION = "application";
/**
 * @internal
 * @brief CHECKIN
 *
 * Used in QFB::TypeProcessor.
 */
static const char *CHECKIN = "checkin";
/**
 * @internal
 * @brief COMMENT
 *
 * Used in QFB::TypeProcessor.
 */
static const char *COMMENT = "comment";
/**
 * @internal
 * @brief DOMAIN
 *
 * Used in QFB::TypeProcessor.
 */
static const char *DOMAIN = "domain";
/**
 * @internal
 * @brief EVENT
 *
 * Used in QFB::TypeProcessor.
 */
static const char *EVENT = "event";
/**
 * @internal
 * @brief FRIENDLIST
 *
 * Used in QFB::TypeProcessor.
 */
static const char *FRIENDLIST = "friendlist";
/**
 * @internal
 * @brief GROUP
 *
 * Used in QFB::TypeProcessor.
 */
static const char *GROUP = "group";
/**
 * @internal
 * @brief INSIGHTS
 *
 * Used in QFB::TypeProcessor.
 */
static const char *INSIGHTS = "insights";
/**
 * @internal
 * @brief LINK
 *
 * Used in QFB::TypeProcessor.
 */
static const char *LINK = "link";
/**
 * @internal
 * @brief MESSAGE
 *
 * Used in QFB::TypeProcessor.
 */
static const char *MESSAGE = "message";
/**
 * @internal
 * @brief NOTE
 *
 * Used in QFB::TypeProcessor.
 */
static const char *NOTE = "note";
/**
 * @internal
 * @brief OFFER
 *
 * Used in QFB::TypeProcessor.
 */
static const char *OFFER = "offer";
/**
 * @internal
 * @brief ORDER
 *
 * Used in QFB::TypeProcessor.
 */
static const char *ORDER = "order";
/**
 * @internal
 * @brief PAGE
 *
 * Used in QFB::TypeProcessor.
 */
static const char *PAGE = "page";
/**
 * @internal
 * @brief PHOTO
 *
 * Used in QFB::TypeProcessor.
 */
static const char *PHOTO = "photo";
/**
 * @internal
 * @brief POST
 *
 * Used in QFB::TypeProcessor.
 */
static const char *POST = "post";
/**
 * @internal
 * @brief QUESTION
 *
 * Used in QFB::TypeProcessor.
 */
static const char *QUESTION = "question";
/**
 * @internal
 * @brief REVIEW
 *
 * Used in QFB::TypeProcessor.
 */
static const char *REVIEW = "review";
/**
 * @internal
 * @brief STATUS
 *
 * Used in QFB::TypeProcessor.
 */
static const char *STATUS = "status";
/**
 * @internal
 * @brief THREAD
 *
 * Used in QFB::TypeProcessor.
 */
static const char *THREAD = "thread";
/**
 * @internal
 * @brief USER
 *
 * Used in QFB::TypeProcessor.
 */
static const char *USER = "user";
/**
 * @internal
 * @brief VIDEO
 *
 * Used in QFB::TypeProcessor.
 */
static const char *VIDEO = "video";

class TypeProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    explicit TypeProcessorPrivate();
    Object *object;
};

TypeProcessorPrivate::TypeProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    object = 0;
}

////// End of private class //////

TypeProcessor::TypeProcessor(QObject *parent):
    AbstractGraphProcessor(*(new TypeProcessorPrivate), parent)
{
}

Object * TypeProcessor::object() const
{
    Q_D(const TypeProcessor);
    return d->object;
}

bool TypeProcessor::processGraphAndArguments(const QString &graph,
                                             const QList<ArgumentPair> &arguments)
{
    Q_UNUSED(arguments)
    QList<ArgumentPair> trueArguments;
    trueArguments.append(ArgumentPair(METADATA_KEY, METADATA_REQUEST_VALUE));
    trueArguments.append(ArgumentPair(FIELDS_KEY, OBJECT_ID_KEY));
    setPreprocessedData(graph, trueArguments);
    return true;
}

bool TypeProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(TypeProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);
    if (d->object) {
        d->object->deleteLater();
    }

    PropertiesMap propertiesMap;

    propertiesMap.insert(OBJECT_ID_KEY, rootObject.value(OBJECT_ID_KEY).toString());

    JsonObject metadata = QFB_JSON_GET_OBJECT(rootObject.value(METADATA_KEY));
    QString type = metadata.value(METADATA_TYPE_VALUE).toString();
    Object::ObjectType trueType = Object::UnknownType;
    if (type == ACHIEVEMENT) {
        trueType = Object::AchievementType;
    } else if (type == ALBUM) {
        trueType = Object::AlbumType;
    } else if (type == APPLICATION) {
        trueType = Object::ApplicationType;
    } else if (type == CHECKIN) {
        trueType = Object::CheckinType;
    } else if (type == COMMENT) {
        trueType = Object::CommentType;
    } else if (type == DOMAIN) {
        trueType = Object::DomainType;
    } else if (type == EVENT) {
        trueType = Object::EventType;
    } else if (type == FRIENDLIST) {
        trueType = Object::FriendListType;
    } else if (type == GROUP) {
        trueType = Object::GroupType;
    } else if (type == INSIGHTS) {
        trueType = Object::InsightsType;
    } else if (type == LINK) {
        trueType = Object::LinkType;
    } else if (type == MESSAGE) {
        trueType = Object::MessageType;
    } else if (type == NOTE) {
        trueType = Object::NoteType;
    } else if (type == OFFER) {
        trueType = Object::OfferType;
    } else if (type == ORDER) {
        trueType = Object::OrderType;
    } else if (type == PAGE) {
        trueType = Object::PageType;
    } else if (type == PHOTO) {
        trueType = Object::PhotoType;
    } else if (type == POST) {
        trueType = Object::PostType;
    } else if (type == QUESTION) {
        trueType = Object::QuestionType;
    } else if (type == REVIEW) {
        trueType = Object::ReviewType;
    } else if (type == STATUS) {
        trueType = Object::StatusType;
    } else if (type == THREAD) {
        trueType = Object::ThreadType;
    } else if (type == USER) {
        trueType = Object::UserType;
    } else if (type == VIDEO) {
        trueType = Object::VideoType;
    } else {
        trueType = Object::UnknownType;
    }

    propertiesMap.insert(OBJECT_TYPE_KEY, trueType);
    d->object = new Object(propertiesMap);
    d->object->moveToThread(QCoreApplication::instance()->thread());

    return true;
}

}
