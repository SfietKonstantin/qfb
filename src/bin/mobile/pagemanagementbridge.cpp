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

#include "pagemanagementbridge.h"
#include <QtCore/QStringList>

PageManagementBridge::PageManagementBridge(QObject *parent) :
    QObject(parent)
{
}

void PageManagementBridge::pop()
{
    emit popRequested();
}

void PageManagementBridge::resolveType(const QString &facebookId, const QString &name)
{
    emit resolveTypeRequested(facebookId, name);
}

void PageManagementBridge::addUserPage(const QString &facebookId, const QString &name)
{
    emit addUserPageRequested(facebookId, name);
}

void PageManagementBridge::addUserInfoPage(const QString &facebookId, const QString &name,
                                           const QString &coverUrl)
{
    emit addUserInfoPageRequested(facebookId, name, coverUrl);
}

void PageManagementBridge::addAlbumListPage(const QString &facebookId, const QString &name,
                                            const QString &coverUrl)
{
    emit addAlbumListPageRequested(facebookId, name, coverUrl);
}

void PageManagementBridge::addPhotoListPage(const QString &facebookId, const QString &name,
                                            const QString &coverUrl)
{
    emit addPhotoListPageRequested(facebookId, name, coverUrl);
}

void PageManagementBridge::addPostPage(const QString &facebookId, const QString &name,
                                       const QString &coverUrl, QFB::Post *post)
{
    emit addPostPageRequested(facebookId, name, coverUrl, post);
}

void PageManagementBridge::showPhoto(QFB::PhotoListModel *model, int index)
{
    emit showPhotoRequested(model, index);
}

void PageManagementBridge::showFeedDialog(const QString &to)
{
    if (to == "me") {
        emit showFeedDialogRequested(QString());
    } else {
        emit showFeedDialogRequested(to);
    }
}
