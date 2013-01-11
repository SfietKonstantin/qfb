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
 * @file user.cpp
 * @brief Implementation of QFB::User
 */

#include "user.h"
#include "private/objectbase_p.h"
#include "private/user_keys_p.h"

namespace QFB
{

User::User(QObject *parent) :
    NamedObject(parent)
{
}

User::User(const PropertiesMap propertiesMap, QObject *parent):
    NamedObject(propertiesMap, parent)
{
    Q_D(ObjectBase);

    // Reparent languages
    QVariantList languagesVariant = d->propertiesMap.value(USER_LANGUAGES_KEY).toList();
    foreach (QVariant languageVariant, languagesVariant) {
        QObject *language = languageVariant.value<NamedObject *>();
        language->setParent(this);
    }

    // Reparent cover
    QObject *coverObject = d->propertiesMap.value(USER_COVER_KEY).value<Cover *>();
    if (coverObject) {
        coverObject->setParent(this);
    }

    // Reparent hometown
    QObject *hometownObject = d->propertiesMap.value(USER_HOMETOWN_KEY).value<NamedObject *>();
    if (hometownObject) {
        hometownObject->setParent(this);
    }

    // Reparent hometown
    QObject *locationObject = d->propertiesMap.value(USER_LOCATION_KEY).value<NamedObject *>();
    if (locationObject) {
        locationObject->setParent(this);
    }

    // Reparent significant other
    QObject *significantOtherObject
            = d->propertiesMap.value(USER_SIGNIFICANT_OTHER_KEY).value<NamedObject *>();
    if (significantOtherObject) {
        significantOtherObject->setParent(this);
    }

}

QString User::firstName() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_FIRST_NAME_KEY).toString();
}

QString User::middleName() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_MIDDLE_NAME_KEY).toString();
}

QString User::lastName() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_LAST_NAME_KEY).toString();
}

User::Gender User::gender() const
{
    Q_D(const ObjectBase);
    int genderInt = d->propertiesMap.value(USER_GENDER_KEY).toInt();
    Gender gender = (Gender) genderInt;
    return gender;
}

QString User::locale() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_LOCALE_KEY).toString();
}

QList<NamedObject *> User::languages() const
{
    Q_D(const ObjectBase);
    QVariantList languagesVariant = d->propertiesMap.value(USER_LANGUAGES_KEY).toList();
    QList<NamedObject *> returnedLanguages;
    foreach (QVariant languageVariant, languagesVariant) {
        returnedLanguages.append(languageVariant.value<NamedObject *>());
    }
    return returnedLanguages;
}

QVariantList User::languagesVariant() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_LANGUAGES_KEY).toList();
}

QUrl User::link() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_LINK_KEY).toUrl();
}

QString User::username() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_USERNAME_KEY).toString();
}

int User::timezone() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_TIMEZONE_KEY).toInt();
}

QDateTime User::updatedTime() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_UPDATED_TIME_KEY).toDateTime();
}

QString User::bio() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_BIO_KEY).toString();
}

QDate User::birthday() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_BIRTHDAY_KEY).toDate();
}

Cover * User::cover() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_COVER_KEY).value<Cover *>();
}

QString User::email() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_EMAIL_KEY).toString();
}

NamedObject * User::hometown() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_HOMETOWN_KEY).value<NamedObject *>();
}

NamedObject * User::location() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_LOCATION_KEY).value<NamedObject *>();
}

QString User::political() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_POLITICAL_KEY).toString();
}

QString User::picture() const
{
//    Q_D(const ObjectBase);
    /// @todo WTF ???
    return QString();
//    return d->propertiesMap.value(user_pic).toString();
}

QString User::quotes() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_QUOTES_KEY).toString();
}

QString User::relationshipStatus() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_RELATIONSHIP_STATUS_KEY).toString();
}

QString User::religion() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_RELIGION_KEY).toString();
}

NamedObject * User::significantOther() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_SIGNIFICANT_OTHER_KEY).value<NamedObject *>();
}

QUrl User::website() const
{
    Q_D(const ObjectBase);
    return d->propertiesMap.value(USER_WEBSITE_KEY).toUrl();
}


}
