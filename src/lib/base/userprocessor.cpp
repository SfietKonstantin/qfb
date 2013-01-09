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

#include "userprocessor.h"
#include "abstractgraphprocessor_p.h"
#include <QtCore/QCoreApplication>
#include "cover_keys_p.h"
#include "helper_p.h"
#include "jsonhelper_p.h"
#include "namedobject_keys_p.h"
#include "object_keys_p.h"
#include "user.h"
#include "user_keys_p.h"

/**
 * @internal
 * @brief GENDER_MALE
 *
 * Used in QFB::UserProcessor
 */
static const char *GENDER_MALE = "male";
/**
 * @internal
 * @brief GENDER_FEMALE
 *
 * Used in QFB::UserProcessor
 */
static const char *GENDER_FEMALE = "female";

namespace QFB
{

class UserProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    explicit UserProcessorPrivate();
    User *user;
};

UserProcessorPrivate::UserProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    user = 0;
}

////// End of private class //////

UserProcessor::UserProcessor(QObject *parent):
    AbstractGraphProcessor(*(new UserProcessorPrivate), parent)
{
}

User * UserProcessor::user() const
{
    Q_D(const UserProcessor);
    return d->user;
}

bool UserProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(UserProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);

    PropertiesMap propertiesMap;
    propertiesMap.insert(OBJECT_ID_KEY, rootObject.value(OBJECT_ID_KEY).toString());
    propertiesMap.insert(NAMEDOBJECT_NAME_KEY, rootObject.value(NAMEDOBJECT_NAME_KEY).toString());
    propertiesMap.insert(USER_FIRST_NAME_KEY, rootObject.value(USER_FIRST_NAME_KEY).toString());
    propertiesMap.insert(USER_MIDDLE_NAME_KEY, rootObject.value(USER_MIDDLE_NAME_KEY).toString());
    propertiesMap.insert(USER_LAST_NAME_KEY, rootObject.value(USER_LAST_NAME_KEY).toString());

    QString genderString = rootObject.value(USER_GENDER_KEY).toString();
    if (genderString == GENDER_MALE) {
        propertiesMap.insert(USER_GENDER_KEY, (int) User::Male);
    } else if (genderString == GENDER_FEMALE) {
        propertiesMap.insert(USER_GENDER_KEY, (int) User::Female);
    } else {
        propertiesMap.insert(USER_GENDER_KEY, (int) User::Unknown);
    }

    propertiesMap.insert(USER_LOCALE_KEY, rootObject.value(USER_LOCALE_KEY).toString());

    JsonArray languages = QFB_JSON_GET_ARRAY(rootObject.value(USER_LANGUAGES_KEY));
    QVariantList languagesVariant;
    foreach (JsonValue language, languages) {
        if (QFB_JSON_IS_OBJECT(language)) {
            JsonObject languageObject = QFB_JSON_GET_OBJECT(language);
            if (languageObject.contains(OBJECT_ID_KEY)
                && languageObject.contains(NAMEDOBJECT_NAME_KEY)) {
                PropertiesMap languagePropertiesMap;
                languagePropertiesMap.insert(OBJECT_ID_KEY,
                                             languageObject.value(OBJECT_ID_KEY).toString());
                languagePropertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                                             languageObject.value(NAMEDOBJECT_NAME_KEY).toString());
                NamedObject *language = new NamedObject(languagePropertiesMap);
                languagesVariant.append(QVariant::fromValue(language));
            }
        }
    }
    propertiesMap.insert(USER_LANGUAGES_KEY, languagesVariant);
    propertiesMap.insert(USER_LINK_KEY, parseUrl(rootObject.value(USER_LINK_KEY).toString()));
    propertiesMap.insert(USER_USERNAME_KEY, rootObject.value(USER_USERNAME_KEY).toString());
    propertiesMap.insert(USER_TIMEZONE_KEY, (int) rootObject.value(USER_TIMEZONE_KEY).toDouble());
    QDateTime updateTime = QDateTime::fromString(rootObject.value(USER_UPDATED_TIME_KEY).toString(),
                                                 Qt::ISODate);
    propertiesMap.insert(USER_UPDATED_TIME_KEY, updateTime);
    propertiesMap.insert(USER_BIO_KEY, rootObject.value(USER_BIO_KEY).toString());

    QString birthdayString = rootObject.value(USER_BIRTHDAY_KEY).toString();
    QDate birthday1 = QDate::fromString(birthdayString, "MM/dd");
    QDate birthday2 = QDate::fromString(birthdayString, "MM/dd/yyyy");
    if (birthday1.isValid()) {
        propertiesMap.insert(USER_BIRTHDAY_KEY, birthday1);
    } else if (birthday2.isValid()) {
        propertiesMap.insert(USER_BIRTHDAY_KEY, birthday2);
    }

    JsonObject cover = QFB_JSON_GET_OBJECT(rootObject.value(USER_COVER_KEY));
    PropertiesMap coverPropertiesMap;
    coverPropertiesMap.insert(OBJECT_ID_KEY, cover.value(OBJECT_ID_KEY).toString());
    coverPropertiesMap.insert(COVER_SOURCE_KEY, parseUrl(cover.value(COVER_SOURCE_KEY).toString()));
    coverPropertiesMap.insert(COVER_OFFSET_Y_KEY, cover.value(COVER_OFFSET_Y_KEY).toDouble());
    propertiesMap.insert(USER_COVER_KEY, QVariant::fromValue(new Cover(coverPropertiesMap)));


    propertiesMap.insert(USER_EMAIL_KEY, rootObject.value(USER_EMAIL_KEY).toString());

    JsonObject hometown = QFB_JSON_GET_OBJECT(rootObject.value(USER_HOMETOWN_KEY));
    PropertiesMap hometownPropertiesMap;
    hometownPropertiesMap.insert(OBJECT_ID_KEY, hometown.value(OBJECT_ID_KEY).toString());
    hometownPropertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                                 hometown.value(NAMEDOBJECT_NAME_KEY).toString());
    NamedObject *hometownObject = new NamedObject(hometownPropertiesMap);
    propertiesMap.insert(USER_HOMETOWN_KEY, QVariant::fromValue(hometownObject));

    JsonObject location = QFB_JSON_GET_OBJECT(rootObject.value(USER_LOCATION_KEY));
    PropertiesMap locationPropertiesMap;
    locationPropertiesMap.insert(OBJECT_ID_KEY, location.value(OBJECT_ID_KEY).toString());
    locationPropertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                                 location.value(NAMEDOBJECT_NAME_KEY).toString());
    NamedObject *locationObject = new NamedObject(locationPropertiesMap);
    propertiesMap.insert(USER_LOCATION_KEY, QVariant::fromValue(locationObject));

    propertiesMap.insert(USER_POLITICAL_KEY, rootObject.value(USER_POLITICAL_KEY).toString());
    propertiesMap.insert(USER_QUOTES_KEY, rootObject.value(USER_QUOTES_KEY).toString());
    propertiesMap.insert(USER_RELATIONSHIP_STATUS_KEY,
                         rootObject.value(USER_RELATIONSHIP_STATUS_KEY).toString());
    propertiesMap.insert(USER_RELIGION_KEY, rootObject.value(USER_RELIGION_KEY).toString());

    JsonObject significantOther = QFB_JSON_GET_OBJECT(rootObject.value(USER_SIGNIFICANT_OTHER_KEY));
    PropertiesMap significantOtherPropertiesMap;
    significantOtherPropertiesMap.insert(OBJECT_ID_KEY,
                                         significantOther.value(OBJECT_ID_KEY).toString());
    significantOtherPropertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                                         significantOther.value(NAMEDOBJECT_NAME_KEY).toString());
    NamedObject *significantOtherUser = new NamedObject(significantOtherPropertiesMap);
    propertiesMap.insert(USER_SIGNIFICANT_OTHER_KEY, QVariant::fromValue(significantOtherUser));
    propertiesMap.insert(USER_WEBSITE_KEY, parseUrl(rootObject.value(USER_WEBSITE_KEY).toString()));



    d->user = new User(propertiesMap);
    d->user->moveToThread(QCoreApplication::instance()->thread());

    return true;
}

}
