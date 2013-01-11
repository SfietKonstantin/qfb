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

#include "querymanager.h"
#include "objects/object.h"
#include "objects/namedobject.h"
#include "objects/album.h"
#include "objects/cover.h"
#include "objects/photo.h"
#include "objects/post.h"
#include "objects/user.h"
#include "loaders/typeloader.h"
#include "loaders/imageloader.h"
#include "loaders/pictureloader.h"
#include "loaders/albumloader.h"
#include "loaders/userloader.h"
#include "loaders/poststatusloader.h"
#include "postvalidator.h"
#include "models/albumlistmodel.h"
#include "models/feedmodel.h"
#include "models/friendlistmodel.h"
#include "models/photolistmodel.h"

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
    qmlRegisterUncreatableType<QFB::NamedObject>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBNamedObject",
                                              "QFBNamedObject cannot be created");
    qmlRegisterUncreatableType<QFB::Album>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBAlbum",
                                           "QFBAlbum be created");
    qmlRegisterUncreatableType<QFB::Cover>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBCover",
                                           "QFBCover cannot be created");
    qmlRegisterUncreatableType<QFB::Photo>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPhoto",
                                           "QFBPhoto be created");
    qmlRegisterUncreatableType<QFB::Post>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPost",
                                          "QFBPostcannot be created");
    qmlRegisterUncreatableType<QFB::User>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBUser",
                                          "QFBUser cannot be created");

    qmlRegisterType<QFB::QueryManager>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBQueryManager");
    qmlRegisterType<QFB::PostValidator>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPostValidator");

    qmlRegisterType<QFB::TypeLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBTypeLoader");
    qmlRegisterType<QFB::ImageLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBImageLoader");
    qmlRegisterType<QFB::PictureLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPictureLoader");
    qmlRegisterType<QFB::UserLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBUserLoader");
    qmlRegisterType<QFB::AlbumLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBAlbumLoader");
    qmlRegisterType<QFB::PostStatusLoader>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPostStatusLoader");

    qmlRegisterType<QFB::AlbumListModel>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBAlbumListModel");
    qmlRegisterType<QFB::FeedModel>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBFeedModel");
    qmlRegisterType<QFB::FriendListModel>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBFriendListModel");
    qmlRegisterType<QFB::PhotoListModel>(uri, PLUGIN_VERSION_MAJOR, 0, "QFBPhotoListModel");
}

}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN2(qfbplugin, QFB::BasePlugin4)
#endif
