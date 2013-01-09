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

#ifndef QFB_BASE_GLOBAL_H
#define QFB_BASE_GLOBAL_H

/**
 * @file base_global.h
 * @short Global qfb library header
 */

#include <QtCore/qglobal.h>

/**
 * \page base Base library
 *
 * \todo write this page
 */

/**
 * \namespace QFB
 * @short Namespace for qfb
 */

/**
 * \def QFBBASE_EXPORT
 * @short Library export or import
 */

#if defined(QFBBASE_LIBRARY)
#  define QFBBASE_EXPORT Q_DECL_EXPORT
#else
#  define QFBBASE_EXPORT Q_DECL_IMPORT
#endif

#endif // QFB_BASE_GLOBAL_H
