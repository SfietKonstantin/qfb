/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @file user.cpp
 * @brief Implementation of QFB::User
 */

#include "user.h"
#include "private/helper_p.h"
#include "private/objectbase_p.h"
#include "private/object_creator_p.h"
#include "private/user_keys_p.h"

namespace QFB
{

class UserPrivate: public ObjectBasePrivate
{
public:
    explicit UserPrivate();
    QList<QFB::NamedObject *> languages;
    QFB::Cover * cover;
    QFB::NamedObject * hometown;
    QList<QString> interestedIn;
    QFB::NamedObject * location;
    QFB::NamedObject * significantOther;
};

UserPrivate::UserPrivate():
    ObjectBasePrivate()
{
}

////// End of private class //////

User::User(QObject *parent):
    NamedObject(parent)
{
}

User::User(const QVariantMap propertiesMap, QObject *parent):
    NamedObject(*(new UserPrivate), parent)
{
    Q_D(User);
    d->propertiesMap = propertiesMap;
    // >>>>> custom object creation code
    // TODO: check object creation
    // It was done automatically by a script
    // Create languages
    QVariantList languagesData = d->propertiesMap.take(USER_LANGUAGES_KEY).toList();
    d->languages = createList<QFB::NamedObject>(languagesData, this);
    // Create cover
    QVariantMap coverData = d->propertiesMap.take(USER_COVER_KEY).toMap();
    d->cover = createObject<QFB::Cover>(coverData, this);
    // Create hometown
    QVariantMap hometownData = d->propertiesMap.take(USER_HOMETOWN_KEY).toMap();
    d->hometown = createObject<QFB::NamedObject>(hometownData, this);
    // Create interestedIn
    QVariantList interestedInData = d->propertiesMap.take(USER_INTERESTED_IN_KEY).toList();
    d->interestedIn = createStringList(interestedInData);
    // Create location
    QVariantMap locationData = d->propertiesMap.take(USER_LOCATION_KEY).toMap();
    d->location = createObject<QFB::NamedObject>(locationData, this);
    // Create significantOther
    QVariantMap significantOtherData = d->propertiesMap.take(USER_SIGNIFICANT_OTHER_KEY).toMap();
    d->significantOther = createObject<QFB::NamedObject>(significantOtherData, this);
    // <<<<< custom object creation code
}

QString User::firstName() const
{
    Q_D(const User);
    // >>>>> property first_name
    return d->propertiesMap.value(USER_FIRST_NAME_KEY).toString();
    // <<<<< property first_name
}

QString User::middleName() const
{
    Q_D(const User);
    // >>>>> property middle_name
    return d->propertiesMap.value(USER_MIDDLE_NAME_KEY).toString();
    // <<<<< property middle_name
}

QString User::lastName() const
{
    Q_D(const User);
    // >>>>> property last_name
    return d->propertiesMap.value(USER_LAST_NAME_KEY).toString();
    // <<<<< property last_name
}

QString User::gender() const
{
    Q_D(const User);
    // >>>>> property gender
    return d->propertiesMap.value(USER_GENDER_KEY).toString();
    // <<<<< property gender
}

QString User::locale() const
{
    Q_D(const User);
    // >>>>> property locale
    return d->propertiesMap.value(USER_LOCALE_KEY).toString();
    // <<<<< property locale
}

QList<QFB::NamedObject *> User::languages() const
{
    Q_D(const User);
    // >>>>> property languages
    return d->languages;
    // <<<<< property languages
}

QUrl User::link() const
{
    Q_D(const User);
    // >>>>> property link
    return parseUrl(d->propertiesMap.value(USER_LINK_KEY).toString());
    // <<<<< property link
}

QString User::username() const
{
    Q_D(const User);
    // >>>>> property username
    return d->propertiesMap.value(USER_USERNAME_KEY).toString();
    // <<<<< property username
}

QString User::thirdPartyId() const
{
    Q_D(const User);
    // >>>>> property third_party_id
    return d->propertiesMap.value(USER_THIRD_PARTY_ID_KEY).toString();
    // <<<<< property third_party_id
}

int User::timezone() const
{
    Q_D(const User);
    // >>>>> property timezone
    return d->propertiesMap.value(USER_TIMEZONE_KEY).toString().toInt();
    // <<<<< property timezone
}

QDateTime User::updatedTime() const
{
    Q_D(const User);
    // >>>>> property updated_time
    return d->propertiesMap.value(USER_UPDATED_TIME_KEY).toDateTime();
    // <<<<< property updated_time
}

QString User::bio() const
{
    Q_D(const User);
    // >>>>> property bio
    return d->propertiesMap.value(USER_BIO_KEY).toString();
    // <<<<< property bio
}

QFB::Cover * User::cover() const
{
    Q_D(const User);
    // >>>>> property cover
    return d->cover;
    // <<<<< property cover
}

QString User::email() const
{
    Q_D(const User);
    // >>>>> property email
    return d->propertiesMap.value(USER_EMAIL_KEY).toString();
    // <<<<< property email
}

QFB::NamedObject * User::hometown() const
{
    Q_D(const User);
    // >>>>> property hometown
    return d->hometown;
    // <<<<< property hometown
}

QList<QString> User::interestedIn() const
{
    Q_D(const User);
    // >>>>> property interested_in
    return d->interestedIn;
    // <<<<< property interested_in
}

QFB::NamedObject * User::location() const
{
    Q_D(const User);
    // >>>>> property location
    return d->location;
    // <<<<< property location
}

QString User::political() const
{
    Q_D(const User);
    // >>>>> property political
    return d->propertiesMap.value(USER_POLITICAL_KEY).toString();
    // <<<<< property political
}

QString User::quotes() const
{
    Q_D(const User);
    // >>>>> property quotes
    return d->propertiesMap.value(USER_QUOTES_KEY).toString();
    // <<<<< property quotes
}

QString User::relationshipStatus() const
{
    Q_D(const User);
    // >>>>> property relationship_status
    return d->propertiesMap.value(USER_RELATIONSHIP_STATUS_KEY).toString();
    // <<<<< property relationship_status
}

QString User::religion() const
{
    Q_D(const User);
    // >>>>> property religion
    return d->propertiesMap.value(USER_RELIGION_KEY).toString();
    // <<<<< property religion
}

QFB::NamedObject * User::significantOther() const
{
    Q_D(const User);
    // >>>>> property significant_other
    return d->significantOther;
    // <<<<< property significant_other
}

QString User::website() const
{
    Q_D(const User);
    // >>>>> property website
    return d->propertiesMap.value(USER_WEBSITE_KEY).toString();
    // <<<<< property website
}


// >>>>> custom source code
// <<<<< custom source code

}
