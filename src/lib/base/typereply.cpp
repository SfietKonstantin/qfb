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

#include "typereply.h"
#include "abstractgraphreply_p.h"
#include "jsonhelper_p.h"

namespace QFB
{

/**
 * @internal
 * @brief METADATA_KEY
 *
 * Used in QFB::TypeReply.
 */
static const char *METADATA_KEY = "metadata";
/**
 * @internal
 * @brief METADATA_REQUEST_VALUE
 *
 * Used in QFB::TypeReply.
 */
static const char *METADATA_REQUEST_VALUE = "1";
/**
 * @internal
 * @brief FIELDS_KEY
 *
 * Used in QFB::TypeReply.
 */
static const char *FIELDS_KEY = "fields";
/**
 * @internal
 * @brief ID_KEY
 *
 * Used in QFB::TypeReply.
 */
static const char *ID_KEY = "id";
/**
 * @internal
 * @brief METADATA_TYPE_VALUE
 *
 * Used in QFB::TypeReply.
 */
static const char *METADATA_TYPE_VALUE = "type";
/**
 * @internal
 * @brief ACHIEVEMENT
 *
 * Used in QFB::TypeReply.
 */
static const char *ACHIEVEMENT = "achievement";
/**
 * @internal
 * @brief ALBUM
 *
 * Used in QFB::TypeReply.
 */
static const char *ALBUM = "album";
/**
 * @internal
 * @brief APPLICATION
 *
 * Used in QFB::TypeReply.
 */
static const char *APPLICATION = "application";
/**
 * @internal
 * @brief CHECKIN
 *
 * Used in QFB::TypeReply.
 */
static const char *CHECKIN = "checkin";
/**
 * @internal
 * @brief COMMENT
 *
 * Used in QFB::TypeReply.
 */
static const char *COMMENT = "comment";
/**
 * @internal
 * @brief DOMAIN
 *
 * Used in QFB::TypeReply.
 */
static const char *DOMAIN = "domain";
/**
 * @internal
 * @brief EVENT
 *
 * Used in QFB::TypeReply.
 */
static const char *EVENT = "event";
/**
 * @internal
 * @brief FRIENDLIST
 *
 * Used in QFB::TypeReply.
 */
static const char *FRIENDLIST = "friendlist";
/**
 * @internal
 * @brief GROUP
 *
 * Used in QFB::TypeReply.
 */
static const char *GROUP = "group";
/**
 * @internal
 * @brief INSIGHTS
 *
 * Used in QFB::TypeReply.
 */
static const char *INSIGHTS = "insights";
/**
 * @internal
 * @brief LINK
 *
 * Used in QFB::TypeReply.
 */
static const char *LINK = "link";
/**
 * @internal
 * @brief MESSAGE
 *
 * Used in QFB::TypeReply.
 */
static const char *MESSAGE = "message";
/**
 * @internal
 * @brief NOTE
 *
 * Used in QFB::TypeReply.
 */
static const char *NOTE = "note";
/**
 * @internal
 * @brief OFFER
 *
 * Used in QFB::TypeReply.
 */
static const char *OFFER = "offer";
/**
 * @internal
 * @brief ORDER
 *
 * Used in QFB::TypeReply.
 */
static const char *ORDER = "order";
/**
 * @internal
 * @brief PAGE
 *
 * Used in QFB::TypeReply.
 */
static const char *PAGE = "page";
/**
 * @internal
 * @brief PHOTO
 *
 * Used in QFB::TypeReply.
 */
static const char *PHOTO = "photo";
/**
 * @internal
 * @brief POST
 *
 * Used in QFB::TypeReply.
 */
static const char *POST = "post";
/**
 * @internal
 * @brief QUESTION
 *
 * Used in QFB::TypeReply.
 */
static const char *QUESTION = "question";
/**
 * @internal
 * @brief REVIEW
 *
 * Used in QFB::TypeReply.
 */
static const char *REVIEW = "review";
/**
 * @internal
 * @brief STATUS
 *
 * Used in QFB::TypeReply.
 */
static const char *STATUS = "status";
/**
 * @internal
 * @brief THREAD
 *
 * Used in QFB::TypeReply.
 */
static const char *THREAD = "thread";
/**
 * @internal
 * @brief USER
 *
 * Used in QFB::TypeReply.
 */
static const char *USER = "user";
/**
 * @internal
 * @brief VIDEO
 *
 * Used in QFB::TypeReply.
 */
static const char *VIDEO = "video";


class TypeReplyPrivate: public AbstractGraphReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    TypeReplyPrivate(TypeReply *q);
    /**
     * @internal
     * @brief Object type
     */
    Object *object;
};

TypeReplyPrivate::TypeReplyPrivate(TypeReply *q):
    AbstractGraphReplyPrivate(q)
{
    object = 0;
}

////// End of private class //////

TypeReply::TypeReply(QObject *parent):
    AbstractGraphReply(*(new TypeReplyPrivate(this)), parent)
{
}

TypeReply::TypeReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractGraphReply(*(new TypeReplyPrivate(this)), parent)
{
    Q_D(TypeReply);
    d->networkAccessManager = networkAccessManager;
}

Object * TypeReply::object() const
{
    Q_D(const TypeReply);
    return d->object;
}

QList<ArgumentPair> TypeReply::processArguments(const QList<ArgumentPair> &arguments)
{
    Q_UNUSED(arguments)
    QList<ArgumentPair> trueArguments;
    trueArguments.append(ArgumentPair(METADATA_KEY, METADATA_REQUEST_VALUE));
    trueArguments.append(ArgumentPair(FIELDS_KEY, ID_KEY));
    return trueArguments;
}

bool TypeReply::processData(QIODevice *dataSource)
{
    Q_D(TypeReply);

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

    propertiesMap.insert(IdProperty, rootObject.value(ID_KEY).toString());

    JsonObject metadata = QFB_JSON_GET_OBJECT(rootObject.value(METADATA_KEY));
    QString type = metadata.value(METADATA_TYPE_VALUE).toString();
    Object::ObjectType trueType = Object::Invalid;
    if (type == ACHIEVEMENT) {
        trueType = Object::Achievement;
    } else if (type == ALBUM) {
        trueType = Object::Album;
    } else if (type == APPLICATION) {
        trueType = Object::Application;
    } else if (type == CHECKIN) {
        trueType = Object::Checkin;
    } else if (type == COMMENT) {
        trueType = Object::Comment;
    } else if (type == DOMAIN) {
        trueType = Object::Domain;
    } else if (type == EVENT) {
        trueType = Object::Event;
    } else if (type == FRIENDLIST) {
        trueType = Object::FriendList;
    } else if (type == GROUP) {
        trueType = Object::Group;
    } else if (type == INSIGHTS) {
        trueType = Object::Insights;
    } else if (type == LINK) {
        trueType = Object::Link;
    } else if (type == MESSAGE) {
        trueType = Object::Message;
    } else if (type == NOTE) {
        trueType = Object::Note;
    } else if (type == OFFER) {
        trueType = Object::Offer;
    } else if (type == ORDER) {
        trueType = Object::Order;
    } else if (type == PAGE) {
        trueType = Object::Page;
    } else if (type == PHOTO) {
        trueType = Object::Photo;
    } else if (type == POST) {
        trueType = Object::Post;
    } else if (type == QUESTION) {
        trueType = Object::Question;
    } else if (type == REVIEW) {
        trueType = Object::Review;
    } else if (type == STATUS) {
        trueType = Object::Status;
    } else if (type == THREAD) {
        trueType = Object::Thread;
    } else if (type == USER) {
        trueType = Object::User;
    } else if (type == VIDEO) {
        trueType = Object::Video;
    } else {
        trueType = Object::Invalid;
    }
    propertiesMap.insert(ObjectTypeProperty, trueType);
    d->object = new Object(propertiesMap, this);

    return true;
}

}
