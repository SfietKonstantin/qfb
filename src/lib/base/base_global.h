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
 * @mainpage %QFB, a Qt Facebook library
 *
 * %QFB is a Qt Faceook library that is used to interface Qt and Facebook
 * graph API. It is designed to be portable and smooth.
 *
 * %QFB is splitted into several libraries
 * - \ref base "libqfb", the base library.
 * - \ref login "libqfblogin", a simple library for performing Facebook OAuth2.
 * - \ref import "libqfbimport", additional features, designed to be exposed through QML.
 * - \ref dialogs "libqfbdialogs", a simple library to call Facebook dialogs.
 *
 * %QFB is developed by Lucien XU (@@SfietKonstantin)
 *
 * \page base Base library
 *
 * The QFB base library provides a lot of components that are used to
 * interface Facebook graph API with a Qt / C++ / QML API.
 *
 * This library consists of of a query manager, QFB::QueryManager, that
 * is used to perform the requests to Facebook API, and manage the requests.
 * It also provides a collection of objects, like QFB::Object, QFB::NamedObject
 * or QFB::User that are used to expose the retrived data in a comprehensive
 * form. Those objects are loaded using processors, that are derived from
 * QRunnable, runs in a thread pool and are used to parse the retrived data.
 *
 * In order to use this library, you should instanciate a QFB::QueryManager,
 * and perform requests using the numerous methods of that class.
 *
 * @see QFB::QueryManager
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
