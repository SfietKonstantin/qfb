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
 * @file friendlistreply.cpp
 * @brief Implementation of QFB::FriendListReply
 */

#include "friendlistreply.h"
#include "abstractreply_p.h"

#include <QtCore/QDebug>
#include <QtCore/QIODevice>
#include <QtCore/QVariant>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include "parser.h"
#else
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#endif

#include "friendbase.h"

namespace QFB
{

/**
 * @brief DATA_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *DATA_KEY = "data";
/**
 * @brief NAME_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *NAME_KEY = "name";
/**
 * @brief ID_KEY
 *
 * Used in QFB::FriendListReply.
 */
static const char *ID_KEY = "id";

/**
 * @internal
 * @brief Private class for QFB::FriendListReplyPrivate
 */
class FriendListReplyPrivate: public AbstractReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    FriendListReplyPrivate(FriendListReply *q);
    /**
     * @internal
     * @brief Friend list
     */
    QList<FriendBase *> friendList;
private:
    Q_DECLARE_PUBLIC(FriendListReply)
};

FriendListReplyPrivate::FriendListReplyPrivate(FriendListReply *q):
    AbstractReplyPrivate(q)
{
}

////// End of private class //////

FriendListReply::FriendListReply(QObject *parent):
    AbstractReply(*(new FriendListReplyPrivate(this)), parent)
{
}

FriendListReply::~FriendListReply()
{
    Q_D(FriendListReply);
    qDeleteAll(d->friendList);
}

FriendListReply::FriendListReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractReply(*(new FriendListReplyPrivate(this)), parent)
{
    Q_D(FriendListReply);
    d->networkAccessManager = networkAccessManager;
}

QList<FriendBase *> FriendListReply::friendList() const
{
    Q_D(const FriendListReply);
    return d->friendList;
}

bool FriendListReply::processData(QIODevice *dataSource)
{
    Q_D(FriendListReply);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QJson::Parser parser;
    QVariant parsedValue = parser.parse(dataSource);

    if (!parsedValue.isValid()) {
        return false;
    }

    QVariantMap valueMap = parsedValue.toMap();
    if (!valueMap.contains(DATA_KEY)) {
        return false;
    }

    qDeleteAll(d->friendList);
    d->friendList.clear();

    QVariantList dataList = valueMap.value(DATA_KEY).toList();
    foreach (QVariant dataListEntry, dataList) {
        QVariantMap dataListEntryMap = dataListEntry.toMap();
        if (dataListEntryMap.contains(ID_KEY) && dataListEntryMap.contains(NAME_KEY)) {
            QString id = dataListEntryMap.value(ID_KEY).toString();
            QString name = dataListEntryMap.value(NAME_KEY).toString();
            FriendBase *friendBase = new FriendBase(id, name, this);
            d->friendList.append(friendBase);
        }
    }
#else
    QJsonDocument jsonDocument = QJsonDocument::fromJson(dataSource->readAll());
    if (jsonDocument.isNull()) {
        return false;
    }

    QJsonObject rootObject = jsonDocument.object();
    if (!rootObject.contains(DATA_KEY)) {
        return false;
    }

    qDeleteAll(d->friendList);
    d->friendList.clear();

    QJsonArray dataArray = rootObject.value(DATA_KEY).toArray();
    foreach (QJsonValue value, dataArray) {
        if (value.isObject()) {
            QJsonObject object = value.toObject();
            if (object.contains(ID_KEY) && object.contains(NAME_KEY)) {
                QString id = object.value(ID_KEY).toString();
                QString name = object.value(NAME_KEY).toString();
                qDebug() << id << name;
                FriendBase *friendBase = new FriendBase(id, name, this);
                d->friendList.append(friendBase);
            }
        }
    }
#endif
    return true;
}

}
