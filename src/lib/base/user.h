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

#ifndef QFB_USER_H
#define QFB_USER_H

/**
 * @file user.h
 * @brief Definition of QFB::User
 */


#include "namedobject.h"
#include <QtCore/QDate>
#include <QtCore/QUrl>
#include "cover.h"

namespace QFB
{

/**
 * @brief An user
 *
 * This class represents an user in Facebook.
 * Extending QFB::UserBase, it contains a lot of properties
 * that can be accessed through
 * - firstName()
 * - middleName()
 * - lastName()
 * - gender()
 * - locale()
 * - languages()
 * - link()
 * - username()
 * - timezone()
 * - updatedTime()
 * - bio()
 * - birthday()
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
 * You can choose the fields you want using the fields
 * query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 *
 * These parameters should be add to the query that is used
 * to get an user.
 *
 * @section missing Missing properties
 *
 * Some fields such as currency, devices, education,
 * interested_in, payment_pricepoints,
 * picture, video_upload_limits and work
 * are not yet implemented.
 *
 * Other fields, such as third_party_id, installed and
 * verified are not implemented and might not be implemented.
 *
 * @see QFB::Property
 */
class QFBBASE_EXPORT User : public NamedObject
{
    Q_OBJECT
    Q_ENUMS(Gender)
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
     */
    Q_PROPERTY(Gender gender READ gender CONSTANT)
    /**
     * @short The user's locale
     *
     * Returns a string containing the ISO Language Code and
     * ISO Country Code.
     */
    Q_PROPERTY(QString locale READ locale CONSTANT)
    /**
     * @short The user's languages
     */
    Q_PROPERTY(QVariantList languages READ languagesVariant CONSTANT)
    /**
     * @short The URL of the profile for the user on Facebook
     */
    Q_PROPERTY(QUrl link READ link CONSTANT)
    /**
     * @short The user's Facebook username
     */
    Q_PROPERTY(QString username READ username CONSTANT)
    /// @todo no third_party_id
    /// @todo no installed
    /**
     * @short The user's timezone offset from UTC
     *
     * Available only for the current user.
     */
    Q_PROPERTY(int timezone READ timezone CONSTANT)
    /**
     * @short The last time the user's profile was updated.
     *
     * Changes to the languages, link, timezone, verified, interested_in,
     * favorite_athletes, favorite_teams, and video_upload_limits are not
     * not reflected in this value.
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    /// @todo no verified
    /**
     * @short The user's biography
     */
    Q_PROPERTY(QString bio READ bio CONSTANT)
    /**
     * @short The user's birthday
     *
     * If the user have chosen to hide the year of birth, it will
     * appear as 1900.
     */
    Q_PROPERTY(QDate birthday READ birthday CONSTANT)
    /**
     * @short The user's cover photo
     *
     * (must be explicitly requested using fields=cover parameter)
     */
    Q_PROPERTY(QFB::Cover * cover READ cover CONSTANT)
    /// @todo currency (low priority)
    /// @todo devices (low priority)
    /// @todo education
    /**
     * @short The proxied or contact email address granted by the user
     */
    Q_PROPERTY(QString email READ email CONSTANT)
    /**
     * @short The user's hometown
     */
    Q_PROPERTY(QFB::NamedObject * hometown READ hometown CONSTANT)
    /// @todo interested_in
    /**
     * @short The user's current city
     */
    Q_PROPERTY(QFB::NamedObject * location READ location CONSTANT)
    /**
     * @short The user's political view
     */
    Q_PROPERTY(QString political READ political CONSTANT)
    /// @todo payment_pricepoints (low priority)
    /// @todo favorite_athletes is deprecated
    /// @todo favorite_teams is deprecated
    /**
     * @short The URL of the user's profile pic
     *
     * Only returned if you explicitly specify a 'fields=picture' argument
     * in the request.
     */
    Q_PROPERTY(QString picture READ picture CONSTANT)
    /**
     * @short The user's favorite quotes
     */
    Q_PROPERTY(QString quotes READ quotes CONSTANT)
    /// @todo Do better !
    /**
     * @short The user's relationship status.
     * This value can be Single, In a relationship, Engaged, Married, It's complicated,
     * In an open relationship, Widowed, Separated, Divorced, In a civil union,
     * In a domestic partnership.
     */
    Q_PROPERTY(QString relationshipStatus READ relationshipStatus CONSTANT)
    /**
     * @short The user's religion
     */
    Q_PROPERTY(QString religion READ religion CONSTANT)
    /**
     * @short The user's significant other
     */
    Q_PROPERTY(QFB::NamedObject * significantOther READ significantOther CONSTANT)
    /// @todo video_upload_limits (low priority)
    /**
     * @short The URL of the user's personal website
     */
    Q_PROPERTY(QUrl website READ website CONSTANT)
    /// @todo work
public:
    /**
     * @brief Enumeration describing the gender
     */
    enum Gender {
        /**
         * @short Unknown
         */
        Unknown,
        /**
         * @short Male
         */
        Male,
        /**
         * @short Female
         */
        Female
    };

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
    Gender gender() const;
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
     * @brief Languages as a variant
     *
     * This method is used to transfer information to
     * a QML context. It returns the list of languages
     * as a list of variant.
     *
     * @return languages.
     */
    QVariantList languagesVariant() const;
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
     * @brief Birthday
     * @return birthday.
     */
    QDate birthday() const;
    /**
     * @brief Cover
     * @return cover.
     */
    Cover * cover() const;
    /**
     * @brief Email
     * @return email.
     */
    QString email() const;
    /**
     * @brief Hometown
     * @return hometown.
     */
    NamedObject * hometown() const;
    /**
     * @brief Location
     * @return location.
     */
    NamedObject * location() const;
    /**
     * @brief Political view
     * @return political view.
     */
    QString political() const;
    /**
     * @brief Picture
     * @return picture.
     */
    QString picture() const;
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
    NamedObject * significantOther() const;
    /**
     * @brief Website
     * @return website.
     */
    QUrl website() const;

private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::User *)

#endif // QFB_USER_H
