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
 * @file base_plugin.cpp
 * @short Implementation of QFB::BasePlugin4 or QFB::BasePlugin5
 */

#include <QtCore/QtGlobal>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include "base_plugin4.h"
#include <QtDeclarative/qdeclarative.h>
#else
#include "base_plugin5.h"
#include <QtQml/qqml.h>
#endif

#include "object.h"
#include "userbase.h"
#include "user.h"
#include "friendlistreply.h"
#include "querymanager.h"
#include "friendlistmodel.h"
#include "pictureloader.h"
#include "userloader.h"

namespace QFB
{

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
/**
 * @internal
 * @brief PLUGIN_VERSION_MAJOR
 */
static const int PLUGIN_VERSION_MAJOR = 4;

void BasePlugin4::registerTypes(const char *uri)
#else
/**
 * @internal
 * @brief PLUGIN_VERSION_MAJOR
 */
static const int PLUGIN_VERSION_MAJOR = 5;

void BasePlugin5::registerTypes(const char *uri)
#endif
{
    // @uri org.SfietKonstantin.qfb
    qmlRegisterUncreatableType<QFB::Object>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBObject",
                                            "QFBObject cannot be created");
    qmlRegisterUncreatableType<QFB::UserBase>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBUserBase",
                                              "QFBUserBase cannot be created");
    qmlRegisterUncreatableType<QFB::User>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBUser",
                                          "QFBUsercannot be created");
    qmlRegisterType<QFB::QueryManager>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBQueryManager");
    qmlRegisterType<QFB::FriendListModel>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBFriendListModel");
    qmlRegisterType<QFB::PictureLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPictureLoader");
    qmlRegisterType<QFB::UserLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBUserLoader");
}

}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(qfbplugin, QFB::BasePlugin4)
#endif
