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
import "pages"
import "dialogs"
import "pagemanagement.js" as PageManagement

PageStackWindow {
    id: _window_
    initialPage: mainPage

    Component.onCompleted: {
        LOGIN_MANAGER.clientId = CLIENT_ID
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

    QFBUserLoader {
        id: meLoader
        function load() {
            request("me", "fields=id,name")
        }
        queryManager: QUERY_MANAGER
        onLoaded: {
            if (ME.name == "") {
                ME.facebookId = user.facebookId
                ME.name = user.name
                request("me", "fields=cover")
            } else if (ME.coverUrl == "") {
                ME.coverUrl = user.cover.source
            }
        }
    }

    QFBTypeLoader {
        id: _type_resolver_
        queryManager: QUERY_MANAGER
        property string resolvedName
        onLoaded: {
            var facebookId = _type_resolver_.object.facebookId
            var type = _type_resolver_.object.objectType
            if (type == QFBObject.UserType) {
                PageManagement.addPage("pages/UserPage", {"facebookId": facebookId,
                                                          "name": resolvedName})
            } else {
                unsupportedInfoBanner.parent = _window_.pageStack.currentPage
                unsupportedInfoBanner.show()
            }
            resolvedName = ""
        }
    }

    LoginSheet {
        id: loginSheet
    }

    FeedDialogSheet {
        id: _feed_dialog_
        onAccepted: window.pageStack.currentPage.load()
    }

    MainPage {
        id: mainPage
    }

    InfoBanner {
        id: unsupportedInfoBanner
        text: qsTr("Loading this page is not supported yet")
    }

    InfoBanner {
        id: _launching_web_browser_info_banner_
        text: qsTr("Launching web browser")
    }
}
