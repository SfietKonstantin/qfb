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

#ifndef QFB_USER_H
#define QFB_USER_H

/**
 * @file user.h
 * @brief Definition of QFB::User
 */

#include "namedobject.h"
// >>>>> includes
#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include "cover.h"
// <<<<< includes

namespace QFB {
/**
 * @short An user
 *
 * This class represents an user in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - firstName()
 * - middleName()
 * - lastName()
 * - gender()
 * - locale()
 * - link()
 * - username()
 * - thirdPartyId()
 * - timezone()
 * - updatedTime()
 * - bio()
 * - cover()
 * - email()
 * - hometown()
 * - location()
 * - political()
 * - quotes()
 * - relationshipStatus()
 * - religion()
 * - significantOther()
 * - website()
 *
 * Some of these fields might not be set, because of
 * users hiding them in their settings, or because of
 * missing permissions.
 *
 * You can choose the fields you want using the "fields"
 * query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 *
 * These parameters should be add to the query that is used
 * to get an user
 *
 * @section missing Missing properties
 *
 * Some fields such as birthday,currency,devices,education,paymentPricepoints,picture,securitySettings,videoUploadLimits,work
 * are not yet implemented.
 *
 * @section notImplemented Not implemented
 *
 * Fields installed,favoriteAthletes,favoriteTeams
 * will not be implemented.
 */
class QFBBASE_EXPORT User: public NamedObject
{
    Q_OBJECT
    /**
     * @short The user's first name
     */
    Q_PROPERTY(QString firstName READ firstName CONSTANT)
    /**
     * @short The user's middle name
     */
    Q_PROPERTY(QString middleName READ middleName CONSTANT)
    /**
     * @short The user's last name
     */
    Q_PROPERTY(QString lastName READ lastName CONSTANT)
    /**
     * @short The user's gender
     * 
     * This value is either "female" or "male".
     */
    Q_PROPERTY(QString gender READ gender CONSTANT)
    /**
     * @short The user's locale
     * 
     * This value is a string containing the ISO
     * Language Code and ISO Country Code.
     */
    Q_PROPERTY(QString locale READ locale CONSTANT)
    /**
     * @short The URL of the profile for the user on Facebook
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
    /**
     * @short The user's Facebook username
     */
    Q_PROPERTY(QString username READ username CONSTANT)
    /**
     * @short An anonymous, but unique identifier for the user
     * 
     * This property is only returned if specifically
     * requested via the fields parameter.
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QString thirdPartyId READ thirdPartyId CONSTANT)
    // installed will not be implemented
    /**
     * @short The user's timezone offset from UTC
     * 
     * This property is only available for the current
     * user.
     */
    Q_PROPERTY(int timezone READ timezone CONSTANT)
    /**
     * @short The last time the user's profile was updated
     * 
     * Changes to the languages, link, timezone, verified, interested_in,
     * favorite_athletes, favorite_teams, and video_upload_limits properties
     * are not not reflected in this value.
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    /**
     * @short The user's biography
     */
    Q_PROPERTY(QString bio READ bio CONSTANT)
    /// @todo birthday
    /**
     * @short The user's cover photo
     * 
     * This property is only returned if specifically
     * requested via the fields parameter.
     * 
     * Requires an access token.
     */
    Q_PROPERTY(QFB::Cover * cover READ cover CONSTANT)
    /// @todo currency
    /// @todo devices
    /// @todo education
    /**
     * @short The proxied or contact email address granted by the user
     */
    Q_PROPERTY(QString email READ email CONSTANT)
    /**
     * @short The user's hometown
     * 
     * Requires \e user_hometown or \e friends_hometown.
     */
    Q_PROPERTY(QFB::NamedObject * hometown READ hometown CONSTANT)
    /**
     * @short The user's current city
     * 
     * Requires \e user_location or \e friends_location.
     */
    Q_PROPERTY(QFB::NamedObject * location READ location CONSTANT)
    /**
     * @short The user's political view
     * 
     * Requires \e user_religion_politics or
     * \e friends_religion_politics.
     */
    Q_PROPERTY(QString political READ political CONSTANT)
    /// @todo payment_pricepoints
    // favorite_athletes will not be implemented
    // favorite_teams will not be implemented
    /// @todo picture
    /**
     * @short The user's favorite quotes
     * 
     * Requires \e user_about_me or \e friends_about_me.
     */
    Q_PROPERTY(QString quotes READ quotes CONSTANT)
    /**
     * @short The user's relationship status
     * 
     * This property can take the following values:
     * - Single
     * - In a relationship
     * - Engaged
     * - Married
     * - It's complicated
     * - In an open relationship
     * - Widowed
     * - Separated
     * - Divorced
     * - In a civil union
     * - In a domestic partnership
     * 
     * Requires \e user_relationships or \e friends_relationships.
     */
    Q_PROPERTY(QString relationshipStatus READ relationshipStatus CONSTANT)
    /**
     * @short The user's religion
     * 
     * Requires \e user_religion_politics or
     * \e friends_religion_politics.
     */
    Q_PROPERTY(QString religion READ religion CONSTANT)
    /// @todo security_settings
    /**
     * @short The user's significant other
     * 
     * Requires \e user_relationships or \e friends_relationships.
     */
    Q_PROPERTY(QFB::NamedObject * significantOther READ significantOther CONSTANT)
    /// @todo video_upload_limits
    /**
     * @short The URL of the user's personal website
     * 
     * Requires \e user_website or \e friends_website.
     */
    Q_PROPERTY(QString website READ website CONSTANT)
    /// @todo work
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit User(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit User(const PropertiesMap propertiesMap, QObject *parent = 0);
    /**
     * @brief First name
     * @return first name.
     */
    QString firstName() const;
    /**
     * @brief Middle name
     * @return middle name.
     */
    QString middleName() const;
    /**
     * @brief Last name
     * @return last name.
     */
    QString lastName() const;
    /**
     * @brief Gender
     * @return gender.
     */
    QString gender() const;
    /**
     * @brief Locale
     * @return locale.
     */
    QString locale() const;
    /**
     * @brief Languages
     * @return languages.
     */
    QList<NamedObject *> languages() const;
    /**
     * @brief Link
     * @return link.
     */
    QUrl link() const;
    /**
     * @brief Username
     * @return username.
     */
    QString username() const;
    /**
     * @brief Third party id
     * @return third party id.
     */
    QString thirdPartyId() const;
    /**
     * @brief Timezone
     * @return timezone.
     */
    int timezone() const;
    /**
     * @brief Updated time
     * @return updated time.
     */
    QDateTime updatedTime() const;
    /**
     * @brief Bio
     * @return bio.
     */
    QString bio() const;
    /**
     * @brief Cover
     * @return cover.
     */
    QFB::Cover * cover() const;
    /**
     * @brief Email
     * @return email.
     */
    QString email() const;
    /**
     * @brief Hometown
     * @return hometown.
     */
    QFB::NamedObject * hometown() const;
    /**
     * @brief Interested in
     * @return interested in.
     */
    QList<QString> interestedIn() const;
    /**
     * @brief Location
     * @return location.
     */
    QFB::NamedObject * location() const;
    /**
     * @brief Political
     * @return political.
     */
    QString political() const;
    /**
     * @brief Quotes
     * @return quotes.
     */
    QString quotes() const;
    /**
     * @brief Relationship status
     * @return relationship status.
     */
    QString relationshipStatus() const;
    /**
     * @brief Religion
     * @return religion.
     */
    QString religion() const;
    /**
     * @brief Significant other
     * @return significant other.
     */
    QFB::NamedObject * significantOther() const;
    /**
     * @brief Website
     * @return website.
     */
    QString website() const;
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::User *)


#endif // QFB_USER_H
