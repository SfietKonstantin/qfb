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

#ifndef QFB_PICTURE_P_H
#define QFB_PICTURE_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file picture_p.h
 * @short Some constants used for getting Facebook pictures
 */

namespace QFB
{

/**
 * @internal
 * @brief PICTURE_TYPE_KEY
 */
static const char *PICTURE_TYPE_KEY = "type";
/**
 * @internal
 * @brief PICTURE_TYPE_SQUARE
 */
static const char *PICTURE_TYPE_SQUARE = "square";
/**
 * @internal
 * @brief PICTURE_TYPE_SMALL
 */
static const char *PICTURE_TYPE_SMALL = "small";
/**
 * @internal
 * @brief PICTURE_TYPE_NORMAL
 */
static const char *PICTURE_TYPE_NORMAL = "normal";
/**
 * @internal
 * @brief PICTURE_TYPE_LARGE
 */
static const char *PICTURE_TYPE_LARGE = "large";
/**
 * @internal
 * @brief PICTURE_TYPE_THUMBNAIL
 */
static const char *PICTURE_TYPE_THUMBNAIL = "thumbnail";
/**
 * @internal
 * @brief PICTURE_TYPE_ALBUM
 */
static const char *PICTURE_TYPE_ALBUM = "album";

}

#endif // QFB_PICTURE_P_H
