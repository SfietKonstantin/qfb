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
#include "private/user_keys_p.h"

namespace QFB
{

User::User(QObject *parent):
    NamedObject(parent)
{
}

User::User(const PropertiesMap propertiesMap, QObject *parent):
    NamedObject(propertiesMap, parent)
{
    Q_D(ObjectBase);
    // >>>>> custom reparenting code
    // TODO: check reparenting
    // It was done automatically by a script
    // Reparent languages
    QVariantList languagesList = d->propertiesMap.value(USER_LANGUAGES_KEY).toList();
    foreach (QVariant languagesVariant, languagesList) {
        QObject *languagesObject = languagesVariant.value<NamedObject *>();
        if (languagesObject) {
            languagesObject->setParent(this);
        }
    }
    // Reparent cover
    QObject *coverObject = d->propertiesMap.value(USER_COVER_KEY).value<QFB::Cover *>();
    if (coverObject) {
        coverObject->setParent(this);
    }
    // Reparent hometown
    QObject *hometownObject = d->propertiesMap.value(USER_HOMETOWN_KEY).value<QFB::NamedObject *>();
    if (hometownObject) {
        hometownObject->setParent(this);
    }
    // Reparent location
    QObject *locationObject = d->propertiesMap.value(USER_LOCATION_KEY).value<QFB::NamedObject *>();
    if (locationObject) {
        locationObject->setParent(this);
    }
    // Reparent significantOther
    QObject *significantOtherObject = d->propertiesMap.value(USER_SIGNIFICANT_OTHER_KEY).value<QFB::NamedObject *>();
    if (significantOtherObject) {
        significantOtherObject->setParent(this);
    }
    // <<<<< custom reparenting code
}

QString User::firstName() const
{
    Q_D(const ObjectBase);
    // >>>>> property first_name
    return d->propertiesMap.value(USER_FIRST_NAME_KEY).toString();
    // <<<<< property first_name
}

QString User::middleName() const
{
    Q_D(const ObjectBase);
    // >>>>> property middle_name
    return d->propertiesMap.value(USER_MIDDLE_NAME_KEY).toString();
    // <<<<< property middle_name
}

QString User::lastName() const
{
    Q_D(const ObjectBase);
    // >>>>> property last_name
    return d->propertiesMap.value(USER_LAST_NAME_KEY).toString();
    // <<<<< property last_name
}

QString User::gender() const
{
    Q_D(const ObjectBase);
    // >>>>> property gender
    return d->propertiesMap.value(USER_GENDER_KEY).toString();
    // <<<<< property gender
}

QString User::locale() const
{
    Q_D(const ObjectBase);
    // >>>>> property locale
    return d->propertiesMap.value(USER_LOCALE_KEY).toString();
    // <<<<< property locale
}

QList<NamedObject *> User::languages() const
{
    Q_D(const ObjectBase);
    // >>>>> property languages
    QVariantList variantList = d->propertiesMap.value(USER_LANGUAGES_KEY).toList();
    QList<NamedObject *> returnedData;
    foreach (QVariant entry, variantList) {
        returnedData.append(entry.value<NamedObject *>());
    }
    return returnedData;
    // <<<<< property languages
}

QUrl User::link() const
{
    Q_D(const ObjectBase);
    // >>>>> property link
    return parseUrl(d->propertiesMap.value(USER_LINK_KEY).toString());
    // <<<<< property link
}

QString User::username() const
{
    Q_D(const ObjectBase);
    // >>>>> property username
    return d->propertiesMap.value(USER_USERNAME_KEY).toString();
    // <<<<< property username
}

QString User::thirdPartyId() const
{
    Q_D(const ObjectBase);
    // >>>>> property third_party_id
    return d->propertiesMap.value(USER_THIRD_PARTY_ID_KEY).toString();
    // <<<<< property third_party_id
}

int User::timezone() const
{
    Q_D(const ObjectBase);
    // >>>>> property timezone
    return d->propertiesMap.value(USER_TIMEZONE_KEY).toString().toInt();
    // <<<<< property timezone
}

QDateTime User::updatedTime() const
{
    Q_D(const ObjectBase);
    // >>>>> property updated_time
    return d->propertiesMap.value(USER_UPDATED_TIME_KEY).toDateTime();
    // <<<<< property updated_time
}

QString User::bio() const
{
    Q_D(const ObjectBase);
    // >>>>> property bio
    return d->propertiesMap.value(USER_BIO_KEY).toString();
    // <<<<< property bio
}

QFB::Cover * User::cover() const
{
    Q_D(const ObjectBase);
    // >>>>> property cover
    return d->propertiesMap.value(USER_COVER_KEY).value<QFB::Cover *>();
    // <<<<< property cover
}

QString User::email() const
{
    Q_D(const ObjectBase);
    // >>>>> property email
    return d->propertiesMap.value(USER_EMAIL_KEY).toString();
    // <<<<< property email
}

QFB::NamedObject * User::hometown() const
{
    Q_D(const ObjectBase);
    // >>>>> property hometown
    return d->propertiesMap.value(USER_HOMETOWN_KEY).value<QFB::NamedObject *>();
    // <<<<< property hometown
}

QList<QString> User::interestedIn() const
{
    Q_D(const ObjectBase);
    // >>>>> property interested_in
    QVariantList variantList = d->propertiesMap.value(USER_INTERESTED_IN_KEY).toList();
    QList<QString> returnedData;
    foreach (QVariant entry, variantList) {
        returnedData.append(entry.value<QString>());
    }
    return returnedData;
    // <<<<< property interested_in
}

QFB::NamedObject * User::location() const
{
    Q_D(const ObjectBase);
    // >>>>> property location
    return d->propertiesMap.value(USER_LOCATION_KEY).value<QFB::NamedObject *>();
    // <<<<< property location
}

QString User::political() const
{
    Q_D(const ObjectBase);
    // >>>>> property political
    return d->propertiesMap.value(USER_POLITICAL_KEY).toString();
    // <<<<< property political
}

QString User::quotes() const
{
    Q_D(const ObjectBase);
    // >>>>> property quotes
    return d->propertiesMap.value(USER_QUOTES_KEY).toString();
    // <<<<< property quotes
}

QString User::relationshipStatus() const
{
    Q_D(const ObjectBase);
    // >>>>> property relationship_status
    return d->propertiesMap.value(USER_RELATIONSHIP_STATUS_KEY).toString();
    // <<<<< property relationship_status
}

QString User::religion() const
{
    Q_D(const ObjectBase);
    // >>>>> property religion
    return d->propertiesMap.value(USER_RELIGION_KEY).toString();
    // <<<<< property religion
}

QFB::NamedObject * User::significantOther() const
{
    Q_D(const ObjectBase);
    // >>>>> property significant_other
    return d->propertiesMap.value(USER_SIGNIFICANT_OTHER_KEY).value<QFB::NamedObject *>();
    // <<<<< property significant_other
}

QString User::website() const
{
    Q_D(const ObjectBase);
    // >>>>> property website
    return d->propertiesMap.value(USER_WEBSITE_KEY).toString();
    // <<<<< property website
}


// >>>>> custom source code
// <<<<< custom source code

}
