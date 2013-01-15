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
import com.nokia.extras 1.1
import org.SfietKonstantin.qfb 4.0
import org.SfietKonstantin.qfb.login 4.0

PageStackWindow {
    id: window
    initialPage: mainPage

    Component.onCompleted: {
        LOGIN_MANAGER.clientId = "390204064393625"
        LOGIN_MANAGER.uiType = QFBLoginManager.Mobile
        LOGIN_MANAGER.friendsPermissions = QFBLoginManager.FriendsAboutMe
                                         + QFBLoginManager.FriendsActivities
                                         + QFBLoginManager.FriendsBirthday
                                         + QFBLoginManager.FriendsEducationHistory
                                         + QFBLoginManager.FriendsEvents
                                         + QFBLoginManager.FriendsGroups
                                         + QFBLoginManager.FriendsHometowm
                                         + QFBLoginManager.FriendsInterests
                                         + QFBLoginManager.FriendsLikes
                                         + QFBLoginManager.FriendsLocation
                                         + QFBLoginManager.FriendsNotes
                                         + QFBLoginManager.FriendsPhotos
                                         + QFBLoginManager.FriendsQuestions
                                         + QFBLoginManager.FriendsRelationships
                                         + QFBLoginManager.FriendsRelationshipDetails
                                         + QFBLoginManager.FriendsReligionPolitics
                                         + QFBLoginManager.FriendsStatus
                                         + QFBLoginManager.FriendsSubscriptions
                                         + QFBLoginManager.FriendsVideos
                                         + QFBLoginManager.FriendsWebsite
                                         + QFBLoginManager.FriendsWorkHistory
        LOGIN_MANAGER.userPermissions = QFBLoginManager.UserAboutMe
                                       + QFBLoginManager.UserActivities
                                       + QFBLoginManager.UserBirthday
                                       + QFBLoginManager.UserEducationHistory
                                       + QFBLoginManager.UserEvents
                                       + QFBLoginManager.UserGroups
                                       + QFBLoginManager.UserHometown
                                       + QFBLoginManager.UserInterests
                                       + QFBLoginManager.UserLikes
                                       + QFBLoginManager.UserLocation
                                       + QFBLoginManager.UserNotes
                                       + QFBLoginManager.UserPhotos
                                       + QFBLoginManager.UserQuestions
                                       + QFBLoginManager.UserRelationships
                                       + QFBLoginManager.UserRelationshipDetails
                                       + QFBLoginManager.UserReligionPolitics
                                       + QFBLoginManager.UserStatus
                                       + QFBLoginManager.UserSubscriptions
                                       + QFBLoginManager.UserVideos
                                       + QFBLoginManager.UserWebsite
                                       + QFBLoginManager.UserWorkHistory
                                       + QFBLoginManager.Email
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

    Connections {
        target: PAGE_MANAGEMENT_BRIDGE
        onPopRequested: window.pageStack.pop()
        onAddUserPageRequested: {
            var newPage = window.pageStack.push(Qt.resolvedUrl("UserPage.qml"),
                                                {"facebookId": facebookId, "name": name})
            newPage.load()
        }
        onAddUserInfoPageRequested: {
            var newPage = window.pageStack.push(Qt.resolvedUrl("UserInfoPage.qml"),
                                                {"facebookId": facebookId, "name": name,
                                                 "coverUrl": coverUrl})
            newPage.load()
        }
        onAddAlbumListPageRequested: {
            var newPage = window.pageStack.push(Qt.resolvedUrl("AlbumListPage.qml"),
                                                {"facebookId": facebookId, "name": name,
                                                 "coverUrl": coverUrl})
            newPage.load()
        }
        onAddPhotoListPageRequested: {
            var newPage = window.pageStack.push(Qt.resolvedUrl("PhotoListPage.qml"),
                                                {"facebookId": facebookId, "name": name,
                                                 "coverUrl": coverUrl})
            newPage.load()
        }

        onResolveTypeRequested: {
            currentResolvingTypeObject.name = name
            typeResolver.request(facebookId)
        }
    }


    QtObject {
        id: me
        property string name
        property string coverUrl
    }

    QtObject {
        id: currentResolvingTypeObject
        property string name
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

    QFBTypeLoader {
        id: typeResolver
        queryManager: QUERY_MANAGER
        onLoadingChanged: {
            if (!loading) {
                var facebookId = typeResolver.object.facebookId
                var type = typeResolver.object.objectType
                if (type == QFBObject.UserType) {
                    PAGE_MANAGEMENT_BRIDGE.addUserPage(facebookId, currentResolvingTypeObject.name)
                } else {
                    unsupportedInfoBanner.parent = window.pageStack.currentPage
                    unsupportedInfoBanner.show()
                }
                currentResolvingTypeObject.name = ""
            }
        }

    }

    LoginSheet {
        id: loginSheet
    }

    MainPage {
        id: mainPage

    }

    InfoBanner {
        id: unsupportedInfoBanner
        text: qsTr("Loading this page is not supported yet")
    }
}
