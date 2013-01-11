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
import org.SfietKonstantin.qfb 4.0
import org.SfietKonstantin.qfb.login 4.0

Item {
    id: container
    width: 480
    height: 600
    property QtObject queryManager: queryManager

    QFBLoginManager {
        id: qfbLoginManager
        clientId: "390204064393625"
        extendedPermissions: QFBLoginManager.ReadStream
        userPermissions: QFBLoginManager.UserBirthday + QFBLoginManager.Email
                         + QFBLoginManager.UserAboutMe + QFBLoginManager.UserLikes
                         + QFBLoginManager.UserEducationHistory
                         + QFBLoginManager.UserRelationshipDetails
                         + QFBLoginManager.UserReligionPolitics
                         + QFBLoginManager.UserRelationships
                         + QFBLoginManager.UserPhotos
        friendsPermissions: QFBLoginManager.FriendsBirthday
                            + QFBLoginManager.FriendsAboutMe + QFBLoginManager.FriendsLikes
                            + QFBLoginManager.FriendsEducationHistory
                            + QFBLoginManager.FriendsRelationshipDetails
                            + QFBLoginManager.FriendsReligionPolitics
                            + QFBLoginManager.FriendsRelationships
                            + QFBLoginManager.FriendsPhotos
        uiType: QFBLoginManager.Mobile
        onUrlRequested: webView.url = url
        Component.onCompleted: {
            if (BRIDGE.token == "") {
                qfbLoginManager.login()
            } else {
                queryManager.token = BRIDGE.token
                webView.visible = false
                friendListModel.request("me/friends")
                postStatusLoader.request("me/feed")
            }
        }

        onLoginSucceeded: {
            BRIDGE.token = token
            queryManager.token = token
            webView.visible = false
            friendListModel.request("me/friends")
            postStatusLoader.request("me/feed")
        }
    }

    QFBQueryManager {
        id: queryManager
    }

    QFBFriendListModel {
        id: friendListModel
        queryManager: queryManager
        autoLoadNext: true
    }

    QFBFeedModel {
        id: feedModel
        queryManager: queryManager
    }

    QFBUserLoader {
        id: userLoader
        queryManager: queryManager
        onUserChanged: {
            console.debug(user.facebookId)
            console.debug(user.name)
            console.debug(user.firstName)
            console.debug(user.middleName)
            console.debug(user.lastName)
            console.debug(user.gender)
            console.debug(user.locale)
            console.debug(user.link)
            console.debug(user.username)
            console.debug(user.timezone)
            console.debug(user.updatedTime)
            console.debug(user.bio)
            console.debug(user.birthday)
            console.debug(user.email)
            console.debug(user.hometown.facebookId)
            console.debug(user.hometown.name)
            console.debug(user.location.facebookId)
            console.debug(user.location.name)
            console.debug(user.political)
            console.debug(user.quotes)
            console.debug(user.relationshipStatus)
            console.debug(user.religion)
            console.debug(user.significantOther.facebookId)
            console.debug(user.significantOther.name)
        }
    }

    Item {
        anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right
        anchors.bottom: toolbar.top

        ListView {
            id: friendsView
            anchors.fill: parent
            model: friendListModel
            delegate: Item {
                width: friendsView.width
                height: 60

                Image {
                    width: 40
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left; anchors.leftMargin: 20
                    source: pictureLoader.picturePath
                    asynchronous: true

                    QFBPictureLoader {
                        id: pictureLoader
                        queryManager: container.queryManager
                        Component.onCompleted: request(model.data.facebookId + "/picture")
                    }
                }

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 20
                    text: model.data.name
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        userLoader.request(model.data.facebookId)
                    }
                }
            }

        }
        ListView {
            id: feedView
            anchors.fill: parent
            model: feedModel
            visible: false
            delegate:Item {
                width: feedView.width
                height: column.height + 20

                Column {
                    id: column
                    width: parent.width - 20
                    anchors.centerIn: parent
                    spacing: 5

                    Text {
                        width: parent.width
                        font.pixelSize: 20
                        text: model.data.from.name
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.message
                        wrapMode: Text.WordWrap
                    }

                    Image {
                        source: model.data.picture
                        asynchronous: true
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.link
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.name
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.caption
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.description
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.source
                    }

                    Text {
                        width: parent.width
                        font.pixelSize: 14
                        text: model.data.type
                    }

                    Image {
                        source: model.data.icon
                        asynchronous: true
                    }
                }

            }
        }
    }

    Rectangle {
        id: toolbar
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        height: 40

        Rectangle {
            height: 40
            width: toolbar.width / 2
            color: "red"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    friendsView.visible = true
                    feedView.visible = false
                }
            }
        }

        Rectangle {
            height: 40
            width: toolbar.width / 2
            color: "blue"
            anchors.right: parent.right

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    friendsView.visible = false
                    feedView.visible = true
                    feedModel.request("me/home")
                }
            }
        }
    }


    WebView {
        id: webView
        preferredWidth: container.width
        anchors.fill: parent
        onUrlChanged: qfbLoginManager.checkUrl(url)
    }
}
