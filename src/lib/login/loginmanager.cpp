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

/**
 * @file loginmanager.cpp
 * @short Implementation of QFB::LoginManager
 */

#include "loginmanager.h"

#include <QtCore/QDebug>
#include <QtCore/QRegExp>
#include <QtCore/QStringList>
#include <QtCore/QUrl>

namespace QFB
{

/**
 * @internal
 * @brief Private class for LoginManager
 */
class LoginManagerPrivate
{
public:
    /**
     * @internal
     * @brief Translate permissions
     * @param permissions permissions.
     * @return a string used in the token query.
     */
    static QString translatePermissions(LoginManager::Permissions permissions);
    /**
     * @internal
     * @brief Client ID
     */
    QString clientId;
    /**
     * @internal
     * @brief Permissions
     */
    LoginManager::Permissions permissions;
    /**
     * @internal
     * @brief UI type
     */
    LoginManager::UiType uiType;
};

QString LoginManagerPrivate::translatePermissions(LoginManager::Permissions permissions)
{
    QStringList permissionsStringList;
    if (permissions.testFlag(LoginManager::ReadFriendList)) {
        permissionsStringList.append("read_friendlists");
    }
    if (permissions.testFlag(LoginManager::ReadInsights)) {
        permissionsStringList.append("read_insights");
    }
    if (permissions.testFlag(LoginManager::ReadMailbox)) {
        permissionsStringList.append("read_mailbox");
    }
    if (permissions.testFlag(LoginManager::ReadRequests)) {
        permissionsStringList.append("read_requests");
    }
    if (permissions.testFlag(LoginManager::ReadStream)) {
        permissionsStringList.append("read_stream");
    }
    if (permissions.testFlag(LoginManager::XmppLogin)) {
        permissionsStringList.append("xmpp_login");
    }
    if (permissions.testFlag(LoginManager::CreateEvent)) {
        permissionsStringList.append("create_event");
    }
    if (permissions.testFlag(LoginManager::ManageFriendList)) {
        permissionsStringList.append("manage_friendlists");
    }
    if (permissions.testFlag(LoginManager::ManageNotifications)) {
        permissionsStringList.append("manage_notifications");
    }
    if (permissions.testFlag(LoginManager::UserOnlinePresence)) {
        permissionsStringList.append("user_online_presence");
    }
    if (permissions.testFlag(LoginManager::FriendsOnlinePresence)) {
        permissionsStringList.append("friends_online_presence");
    }
    if (permissions.testFlag(LoginManager::PublishCheckins)) {
        permissionsStringList.append("publish_checkins");
    }
    if (permissions.testFlag(LoginManager::PublishStream)) {
        permissionsStringList.append("publish_stream");
    }
    if (permissions.testFlag(LoginManager::RsvpEvent)) {
        permissionsStringList.append("rsvp_event");
    }
    if (permissions.testFlag(LoginManager::UserAboutMe)) {
        permissionsStringList.append("user_about_me");
    }
    if (permissions.testFlag(LoginManager::FriendsAboutMe)) {
        permissionsStringList.append("friends_about_me");
    }
    if (permissions.testFlag(LoginManager::UserActivities)) {
        permissionsStringList.append("user_activities");
    }
    if (permissions.testFlag(LoginManager::FriendsActivities)) {
        permissionsStringList.append("friends_activities");
    }
    if (permissions.testFlag(LoginManager::UserBirthday)) {
        permissionsStringList.append("user_birthday");
    }
    if (permissions.testFlag(LoginManager::FriendsBirthday)) {
        permissionsStringList.append("friends_birthday");
    }
    return permissionsStringList.join(",");
}

////// End of private class //////

LoginManager::LoginManager(QObject *parent):
    QObject(parent), d_ptr(new LoginManagerPrivate)
{
    Q_D(LoginManager);
    d->permissions = Permissions();
    d->uiType = Desktop;
}

LoginManager::LoginManager(const QString &clientId, QObject *parent):
    QObject(parent), d_ptr(new LoginManagerPrivate)
{
    Q_D(LoginManager);
    d->clientId = clientId;
    d->permissions = Permissions();
    d->uiType = Desktop;
}

LoginManager::LoginManager(const QString &clientId, Permissions permissions, QObject *parent):
    QObject(parent), d_ptr(new LoginManagerPrivate)
{
    Q_D(LoginManager);
    d->clientId = clientId;
    d->permissions = permissions;
    d->uiType = Desktop;
}

LoginManager::LoginManager(const QString &clientId, UiType uiType, QObject *parent):
    QObject(parent), d_ptr(new LoginManagerPrivate)
{
    Q_D(LoginManager);
    d->clientId = clientId;
    d->permissions = Permissions();
    d->uiType = uiType;
}

LoginManager::LoginManager(const QString &clientId, Permissions permissions, UiType uiType,
                           QObject *parent):
    QObject(parent), d_ptr(new LoginManagerPrivate)
{
    Q_D(LoginManager);
    d->clientId = clientId;
    d->permissions = permissions;
    d->uiType = uiType;
}

LoginManager::~LoginManager()
{
}

QString LoginManager::clientId() const
{
    Q_D(const LoginManager);
    return d->clientId;
}

LoginManager::Permissions LoginManager::permissions() const
{
    Q_D(const LoginManager);
    return d->permissions;
}

LoginManager::UiType LoginManager::uiType() const
{
    Q_D(const LoginManager);
    return d->uiType;
}

void LoginManager::setClientId(const QString &clientId)
{
    Q_D(LoginManager);
    if (d->clientId != clientId) {
        d->clientId = clientId;
        emit clientIdChanged();
    }
}

void LoginManager::setPermissions(Permissions permissions)
{
    Q_D(LoginManager);
    if (d->permissions != permissions) {
        d->permissions = permissions;
        emit permissionsChanged();
    }
}

void LoginManager::setUiType(UiType uiType)
{
    Q_D(LoginManager);
    if (d->uiType != uiType) {
        d->uiType = uiType;
        emit uiTypeChanged();
    }
}

void LoginManager::login()
{
    Q_D(LoginManager);
    QString permissions = d->translatePermissions(d->permissions);
    qDebug() << "Asked permissions" << permissions;

    QString url ("https://%1.facebook.com/dialog/oauth?client_id=%2&\
redirect_uri=https://www.facebook.com/connect/login_success.html&scope=%3&response_type=token");

    switch (d->uiType) {
        case Mobile:
            url = url.arg("m", d->clientId, permissions);
            break;
        default:
            url = url.arg("www", d->clientId, permissions);
            break;
    }

    emit urlRequested(QUrl(url));
}

void LoginManager::checkUrl(const QUrl &url)
{
    Q_D(LoginManager);

    QString urlToString = url.toString();
    // Check if the URL is not good
    if (!urlToString.contains(d->clientId)) {
        if (urlToString.contains("https://www.facebook.com/connect/login_success.html")) {
            // Get the token
            QRegExp tokenRegExp ("access_token=([^&]*)&");
            if (url.fragment().indexOf(tokenRegExp) != -1) {
                QString token = tokenRegExp.cap(1);

                qDebug() << "Login succeded";
                qDebug() << "Token:" << token;
                emit loginSucceeded(token);
                return;
            } else {
                qDebug() << "Login failed";
                emit loginFailed();
                return;
            }
        }
        qDebug() << "The user clicked on a wrong link !";
        login();
    }
}

}
