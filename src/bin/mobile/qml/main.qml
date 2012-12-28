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

import QtQuick 1.1
import QtWebKit 1.0
import com.nokia.meego 1.0
import org.SfietKonstantin.qfb 4.0
import org.SfietKonstantin.qfb.login 4.0

PageStackWindow {
    id: window
    initialPage: mainPage

    Component.onCompleted: {
        LOGIN_MANAGER.clientId = "390204064393625"
        LOGIN_MANAGER.uiType = QFBLoginManager.Mobile
        LOGIN_MANAGER.friendsPermissions = QFBLoginManager.FriendsBirthday
                                           + QFBLoginManager.FriendsAboutMe
                                           + QFBLoginManager.FriendsLikes
                                           + QFBLoginManager.FriendsEducationHistory
                                           + QFBLoginManager.FriendsRelationshipDetails
                                           + QFBLoginManager.FriendsReligionPolitics
                                           + QFBLoginManager.FriendsRelationships
        LOGIN_MANAGER.userPermissions = QFBLoginManager.UserBirthday + QFBLoginManager.Email
                                        + QFBLoginManager.UserAboutMe + QFBLoginManager.UserLikes
                                        + QFBLoginManager.UserEducationHistory
                                        + QFBLoginManager.UserRelationshipDetails
                                        + QFBLoginManager.UserReligionPolitics
                                        + QFBLoginManager.UserRelationships
        LOGIN_MANAGER.extendedPermissions = QFBLoginManager.ReadFriendList
                                            + QFBLoginManager.ReadInsights
                                            + QFBLoginManager.ReadMailbox
                                            + QFBLoginManager.ReadRequests
                                            + QFBLoginManager.ReadStream
                                            + QFBLoginManager.XmppLogin
                                            + QFBLoginManager.AdsManagement
                                            + QFBLoginManager.CreateEvent
                                            + QFBLoginManager.ManageFriendList
                                            + QFBLoginManager.ManageNotifications
                                            + QFBLoginManager.UserOnlinePresence
                                            + QFBLoginManager.FriendsOnlinePresence
                                            + QFBLoginManager.PublishCheckins
                                            + QFBLoginManager.PublishStream
                                            + QFBLoginManager.RsvpEvent
        if (TOKEN_MANAGER.token == "") {
            loginSheet.open()
            LOGIN_MANAGER.login()
        } else {
            QUERY_MANAGER.token = TOKEN_MANAGER.token
        }
    }

    Connections {
        target: LOGIN_MANAGER
        onLoginSucceeded: {
            QUERY_MANAGER.token = token
            TOKEN_MANAGER.token = token
            loginSheet.close()
        }
    }

    Connections {
        target: QUERY_MANAGER
        onTokenChanged: {
            if (QUERY_MANAGER.token != "") {
                meLoader.load()
            }
        }
    }


    QtObject {
        id: me
        property string name
        property string coverUrl

    }

    QFBUserLoader {
        id: meLoader
        function load() {
            request("me", "fields=name")
        }
        queryManager: QUERY_MANAGER
        onLoadingChanged: {
            if (!loading) {
                if (me.name == "") {
                    me.name = user.name
                    request("me", "fields=cover")
                } else if (me.coverUrl == "") {
                    me.coverUrl = user.cover.source
                }
            }
        }
    }

    LoginSheet {
        id: loginSheet
        loginManager: loginManager
    }

    MainPage {
        id: mainPage
    }

}
