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
     * @short The user's full name
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
     * @short The URL of the profile for the user on Facebook
     */
    Link,
    /**
     * @short The user's Facebook username
     */
    Username,
    /**
     * @short The user's biography
     */
    Bio,
    /**
     * @short The user's birthday
     *
     * Requires \e user_birthday  or \e friends_birthday.
     * This entry is currently not working very well.
     */
    Birthday
};

}

#endif // QFB_QFB_H
