/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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
 * @internal
 * @file dialogs_plugin.cpp
 * @short Implementation of QFB::DialogsPlugin4 or QFB::DialogsPlugin5
 */

#include <QtCore/QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include "dialogs_plugin4.h"
#include <QtDeclarative/qdeclarative.h>
#else
#include "dialogs_plugin5.h"
#include <QtQml/qqml.h>
#endif

#include "feeddialogmanager.h"

namespace QFB
{

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
/**
 * @internal
 * @brief PLUGIN_VERSION_MAJOR
 */
static const int PLUGIN_VERSION_MAJOR = 4;

void DialogsPlugin4::registerTypes(const char *uri)
#else
/**
 * @internal
 * @brief PLUGIN_VERSION_MAJOR
 */
static const int PLUGIN_VERSION_MAJOR = 5;

void DialogsPlugin5::registerTypes(const char *uri)
#endif
{
    // @uri org.SfietKonstantin.qfb.dialogs
    qmlRegisterType<QFB::FeedDialogManager>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBFeedDialogManager");
}

}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(qfbplugin, QFB::DialogsPlugin4)
#endif
