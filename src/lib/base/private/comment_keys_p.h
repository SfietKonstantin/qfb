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

#ifndef QFB_COMMENT_KEYS_P_H
#define QFB_COMMENT_KEYS_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file comment_keys_p.h
 * @brief Definition of internal keys associated to QFB::Comment
 */

namespace QFB
{

/**
 * @internal
 * @brief COMMENT_FROM_KEY
 */
static const char *COMMENT_FROM_KEY = "from";
/**
 * @internal
 * @brief COMMENT_MESSAGE_KEY
 */
static const char *COMMENT_MESSAGE_KEY = "message";
/**
 * @internal
 * @brief COMMENT_CREATED_TIME_KEY
 */
static const char *COMMENT_CREATED_TIME_KEY = "created_time";
/**
 * @internal
 * @brief COMMENT_USER_LIKES_KEY
 */
static const char *COMMENT_USER_LIKES_KEY = "user_likes";
/**
 * @internal
 * @brief COMMENT_TYPE_KEY
 */
static const char *COMMENT_TYPE_KEY = "type";

}

#endif // QFB_COMMENT_KEYS_P_H
