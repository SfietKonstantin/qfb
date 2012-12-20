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
 * @file userreply.cpp
 * @brief Implementation of QFB::UserReply
 */

#include "userreply.h"
#include "abstractgraphreply_p.h"

#include "helper_p.h"
#include "user.h"
#include "language.h"
#include "jsonhelper_p.h"

#include <QtCore/QDebug>

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
 * @brief LANGUAGES_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *LANGUAGES_KEY = "languages";
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
/**
 * @internal
 * @brief COVER_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *COVER_KEY = "cover";
/**
 * @internal
 * @brief SOURCE_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *SOURCE_KEY = "source";
/**
 * @internal
 * @brief OFFSET_Y_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *OFFSET_Y_KEY = "offset_y";
/**
 * @internal
 * @brief EMAIL_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *EMAIL_KEY = "email";
/**
 * @internal
 * @brief POLITICAL_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *POLITICAL_KEY = "political";
/**
 * @internal
 * @brief QUOTES_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *QUOTES_KEY = "quotes";
/**
 * @internal
 * @brief RELATIONSHIP_STATUS_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *RELATIONSHIP_STATUS_KEY = "relationship_status";
/**
 * @internal
 * @brief RELIGION_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *RELIGION_KEY = "religion";
/**
 * @internal
 * @brief SIGNIFICANT_OTHER_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *SIGNIFICANT_OTHER_KEY = "significant_other";
/**
 * @internal
 * @brief WEBSITE_KEY
 *
 * Used in QFB::UserReply.
 */
static const char *WEBSITE_KEY = "website";

/**
 * @internal
 * @brief Private class for QFB::UserReply
 */
class UserReplyPrivate: public AbstractGraphReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    UserReplyPrivate(UserReply *q);
    /**
     * @internal
     * @brief User
     */
    User *user;
};

UserReplyPrivate::UserReplyPrivate(UserReply *q):
    AbstractGraphReplyPrivate(q)
{
    user = 0;
}

////// End of private class //////

UserReply::UserReply(QObject *parent) :
    AbstractGraphReply(*(new UserReplyPrivate(this)), parent)
{
}

UserReply::UserReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractGraphReply(*(new UserReplyPrivate(this)), parent)
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

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);
    if (d->user) {
        d->user->deleteLater();
    }

    PropertiesMap propertiesMap;
    propertiesMap.insert(IdProperty, rootObject.value(ID_KEY).toString());
    propertiesMap.insert(NameProperty, rootObject.value(NAME_KEY).toString());
    propertiesMap.insert(FirstNameProperty, rootObject.value(FIRST_NAME_KEY).toString());
    propertiesMap.insert(MiddleNameProperty, rootObject.value(MIDDLE_NAME_KEY).toString());
    propertiesMap.insert(LastNameProperty, rootObject.value(LAST_NAME_KEY).toString());
    propertiesMap.insert(GenderProperty, rootObject.value(GENDER_KEY).toString());
    propertiesMap.insert(LocaleProperty, rootObject.value(LOCALE_KEY).toString());

    JsonArray languages = QFB_JSON_GET_ARRAY(rootObject.value(LANGUAGES_KEY));
    QVariantList languagesVariant;
    foreach (JsonValue language, languages) {
        if (QFB_JSON_IS_OBJECT(language)) {
            JsonObject languageObject = QFB_JSON_GET_OBJECT(language);
            if (languageObject.contains(ID_KEY) && languageObject.contains(NAME_KEY)) {
                PropertiesMap languagePropertiesMap;
                languagePropertiesMap.insert(IdProperty, languageObject.value(ID_KEY).toString());
                languagePropertiesMap.insert(NameProperty,
                                             languageObject.value(NAME_KEY).toString());
                Language *language = new Language(languagePropertiesMap, this);
                languagesVariant.append(QVariant::fromValue(language));
            }
        }
    }
    propertiesMap.insert(LanguagesProperty, languagesVariant);
    propertiesMap.insert(LinkProperty, parseUrl(rootObject.value(LINK_KEY).toString()));
    propertiesMap.insert(UsernameProperty, rootObject.value(USERNAME_KEY).toString());
    propertiesMap.insert(BioProperty, rootObject.value(BIO_KEY).toString());

    QString birthdayString = rootObject.value(BIRTHDAY_KEY).toString();
    QDate birthday1 = QDate::fromString(birthdayString, "MM/dd");
    QDate birthday2 = QDate::fromString(birthdayString, "MM/dd/yyyy");
    if (birthday1.isValid()) {
        propertiesMap.insert(BirthdayProperty, birthday1);
    } else if (birthday2.isValid()) {
        propertiesMap.insert(BirthdayProperty, birthday2);
    }

    JsonObject cover = QFB_JSON_GET_OBJECT(rootObject.value(COVER_KEY));
    PropertiesMap coverPropertiesMap;
    coverPropertiesMap.insert(IdProperty, cover.value(ID_KEY).toString());
    coverPropertiesMap.insert(SourceProperty, parseUrl(cover.value(SOURCE_KEY).toString()));
    coverPropertiesMap.insert(OffsetYProperty, cover.value(OFFSET_Y_KEY).toDouble());
    propertiesMap.insert(CoverProperty, QVariant::fromValue(new Cover(coverPropertiesMap, this)));


    propertiesMap.insert(EmailProperty, rootObject.value(EMAIL_KEY).toString());
    propertiesMap.insert(PoliticalProperty, rootObject.value(POLITICAL_KEY).toString());
    propertiesMap.insert(QuotesProperty, rootObject.value(QUOTES_KEY).toString());
    propertiesMap.insert(RelationshipStatusProperty,
                         rootObject.value(RELATIONSHIP_STATUS_KEY).toString());
    propertiesMap.insert(ReligionProperty, rootObject.value(RELIGION_KEY).toString());

    JsonObject significantOther = QFB_JSON_GET_OBJECT(rootObject.value(SIGNIFICANT_OTHER_KEY));
    PropertiesMap significantOtherPropertiesMap;
    significantOtherPropertiesMap.insert(IdProperty, significantOther.value(ID_KEY).toString());
    significantOtherPropertiesMap.insert(NameProperty, significantOther.value(NAME_KEY).toString());
    UserBase *significantOtherUser = new UserBase(significantOtherPropertiesMap, this);
    propertiesMap.insert(SignificantOtherProperty, QVariant::fromValue(significantOtherUser));
    propertiesMap.insert(WebsiteProperty, parseUrl(rootObject.value(WEBSITE_KEY).toString()));

    d->user = new User(propertiesMap, this);
    return true;

}

}
