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

#ifndef QFB_QFB_H
#define QFB_QFB_H

/**
 * @file qfb.h
 * @short Global enumerations used in qfb
 */

namespace QFB
{

/**
 * @brief Enumeration describing the properties that a Facebook entry can have
 */
enum Property {
    /**
     * @short The entry's Facebook ID
     */
    Id,
    /**
     * @short The entry's name
     */
    Name,
    /**
     * @short The user's first name
     */
    FirstName,
    /**
     * @short The user's middle name
     */
    MiddleName,
    /**
     * @short The user's last name
     */
    LastName,
    /**
     * @short The user's gender: female or male
     * @todo define an enumeration for that.
     */
    Gender,
    /**
     * @short The user's locale
     *
     * The locale is provided as an ISO Language Code and ISO Country Code.
     */
    Locale,
    /**
     * @short The user's languages
     */
    Languages,
    /**
     * @short The URL of the profile for the user on Facebook
     */
    Link,
    /**
     * @short The user's Facebook username
     */
    Username,
    /**
     * @short The user's timezone offset from UTC
     *
     * Available only for the current user.
     */
    Timezone,
    /**
     * @short The last time the user's profile was updated.
     *
     * Changes to the languages, link, timezone, verified, interested_in, favorite_athletes,
     * favorite_teams, and video_upload_limits are not not reflected in this value.
     */
    UpdatedTime,
    /**
     * @short The user's biography
     */
    Bio,
    /**
     * @short The user's birthday
     *
     * Requires \e user_birthday or \e friends_birthday.
     * This entry is currently not working very well.
     */
    Birthday,
    /**
     * @short The user's cover photo
     *
     * (must be explicitly requested using fields=cover parameter)
     */
    Cover,
    /**
     * @short The user's currency settings
     *
     * (must be explicitly requested using a fields=currency URL parameter)
     */
    Currency,
    /**
     * @short A list of the user's devices beyond desktop
     * @todo comment
     */
    Devices,
    /**
     * A list of the user's education history
     */
    Education,
    /**
     * @short The proxied or contact email address granted by the user
     *
     * Requires \e email.
     */
    Email,
    Hometown,
    InterestedIn,
    Location,
    Political,
    PaymentPricepoints,
    FavoriteAthletes,
    FavoriteTeams,
    Picture,
    Quotes,
    RelationshipStatus,
    Religion,
    SecuritySettings,
    SignificantOther,
    VideoUploadLimits,
    Website,
    Work
};

}

#endif // QFB_QFB_H
