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
 * @file qml/base_plugin.cpp
 * @short Implementation of QFB::BasePlugin
 */

#include <QtCore/QtGlobal>

#include "base_plugin.h"
#include <QtQml/qqml.h>

#include "object.h"
#include "friendbase.h"
#include "friendlistreply.h"
#include "querymanager.h"


namespace QFB
{

void BasePlugin::registerTypes(const char *uri)
{
    // @uri org.SfietKonstantin.qfb
    qmlRegisterType<QFB::Object>(uri, 5, 0, "QFBObject");
    qmlRegisterType<QFB::FriendBase>(uri, 5, 0, "QFBFriendBase");
    qmlRegisterType<QFB::QueryManager>(uri, 5, 0, "QFBQueryManager");
    qmlRegisterType<QFB::FriendListReply>(uri, 5, 0, "QFBFriendListReply");
}

}
