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

#include "userreply.h"
#include "abstractreply_p.h"

#include "user.h"

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include "parser.h"
#else
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#endif

namespace QFB
{

/**
 * @internal
 * @brief ID_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *ID_KEY = "id";
/**
 * @internal
 * @brief NAME_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *NAME_KEY = "name";
/**
 * @internal
 * @brief FIRST_NAME_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *FIRST_NAME_KEY = "first_name";
/**
 * @internal
 * @brief MIDDLE_NAME_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *MIDDLE_NAME_KEY = "middle_name";
/**
 * @internal
 * @brief LAST_NAME_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *LAST_NAME_KEY = "last_name";
/**
 * @internal
 * @brief GENDER_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *GENDER_KEY = "gender";
/**
 * @internal
 * @brief LOCALE_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *LOCALE_KEY = "locale";
/**
 * @internal
 * @brief LINK_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *LINK_KEY = "link";
/**
 * @internal
 * @brief USERNAME_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *USERNAME_KEY = "username";
/**
 * @internal
 * @brief BIO_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *BIO_KEY = "bio";
/**
 * @internal
 * @brief BIRTHDAY_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *BIRTHDAY_KEY = "birthday";

class UserReplyPrivate: public AbstractReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    UserReplyPrivate(UserReply *q);
    User *user;
};

UserReplyPrivate::UserReplyPrivate(UserReply *q):
    AbstractReplyPrivate(q)
{
    user = 0;
}

////// End of private class //////

UserReply::UserReply(QObject *parent) :
    AbstractReply(*(new UserReplyPrivate(this)), parent)
{
}

UserReply::UserReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractReply(*(new UserReplyPrivate(this)), parent)
{
    Q_D(UserReply);
    d->networkAccessManager = networkAccessManager;
}

User * UserReply::user() const
{
    Q_D(const UserReply);
    return d->user;
}

bool UserReply::processData(QIODevice *dataSource)
{
    Q_D(UserReply);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QJson::Parser parser;
    QVariant parsedValue = parser.parse(dataSource);

    if (!parsedValue.isValid()) {
        setError("Received data is not a JSON document");
        return false;
    }

    QVariantMap valueMap = parsedValue.toMap();
    if (d->user) {
        d->user->deleteLater();
    }

    PropertiesMap propertiesMap;
    propertiesMap.insert(Id, valueMap.value(ID_KEY).toString());
    propertiesMap.insert(Name, valueMap.value(NAME_KEY).toString());
    propertiesMap.insert(FirstName, valueMap.value(FIRST_NAME_KEY).toString());
    propertiesMap.insert(MiddleName, valueMap.value(MIDDLE_NAME_KEY).toString());
    propertiesMap.insert(LastName, valueMap.value(LAST_NAME_KEY).toString());
    propertiesMap.insert(Gender, valueMap.value(GENDER_KEY).toString());
    propertiesMap.insert(Locale, valueMap.value(LOCALE_KEY).toString());
    propertiesMap.insert(Link, valueMap.value(LINK_KEY).toString());
    propertiesMap.insert(Username, valueMap.value(USERNAME_KEY).toString());
    propertiesMap.insert(Bio, valueMap.value(BIO_KEY).toString());
    QDate birthday = QDate::fromString(valueMap.value(BIRTHDAY_KEY).toString(), "MM/dd");
    propertiesMap.insert(Birthday, birthday);
    d->user = new User(propertiesMap, this);
#else
    QJsonDocument jsonDocument = QJsonDocument::fromJson(dataSource->readAll());
    if (jsonDocument.isNull()) {
        setError("Received data is not a JSON document");
        return false;
    }

    QJsonObject rootObject = jsonDocument.object();
    if (d->user) {
        d->user->deleteLater();
    }


    PropertiesMap propertiesMap;
    propertiesMap.insert(Id, rootObject.value(ID_KEY).toString());
    propertiesMap.insert(Name, rootObject.value(NAME_KEY).toString());
    propertiesMap.insert(FirstName, rootObject.value(FIRST_NAME_KEY).toString());
    propertiesMap.insert(MiddleName, rootObject.value(MIDDLE_NAME_KEY).toString());
    propertiesMap.insert(LastName, rootObject.value(LAST_NAME_KEY).toString());
    propertiesMap.insert(Gender, rootObject.value(GENDER_KEY).toString());
    propertiesMap.insert(Locale, rootObject.value(LOCALE_KEY).toString());
    propertiesMap.insert(Link, rootObject.value(LINK_KEY).toString());
    propertiesMap.insert(Username, rootObject.value(USERNAME_KEY).toString());
    propertiesMap.insert(Bio, rootObject.value(BIO_KEY).toString());
    QDate birthday = QDate::fromString(rootObject.value(BIRTHDAY_KEY).toString(), "MM/dd");
    propertiesMap.insert(Birthday, birthday);
    d->user = new User(propertiesMap, this);
#endif
    return true;

}

}
