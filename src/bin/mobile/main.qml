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
import com.nokia.meego 1.0

PageStackWindow {
    id: window

    Page {
        id: mainPage

        QFBQueryManager {
            id: queryManager
        }

        QFBLoginManager {
            id: qfbLoginManager
            clientId: "390204064393625"
            permissions: QFBLoginManager.ReadFriendList
            uiType: QFBLoginManager.Mobile
            onUrlRequested: webView.url = url
            Component.onCompleted: {
                if (BRIDGE.token == "") {
                    loginSheet.open()
                    qfbLoginManager.login()
                } else {
                    queryManager.token = BRIDGE.token
                }
            }

            onLoginSucceeded: {
                BRIDGE.token = token
                queryManager.token = token
                loginSheet.accept()
            }
        }

        Sheet {
            id: loginSheet
            onRejected: Qt.quit()
            rejectButtonText: qsTr("Cancel")
            content: WebView {
                id: webView
                anchors.fill: parent
                preferredWidth: loginSheet.width
                onUrlChanged: qfbLoginManager.checkUrl(url)
            }
        }


    }

//    QFBLoginManager {
//        id: qfbLoginManager
//        clientId: "390204064393625"
//        permissions: QFBLoginManager.ReadFriendList
//        uiType: QFBLoginManager.Mobile
//        onUrlRequested: webView.url = url
//        Component.onCompleted: {
//            if (BRIDGE.token == "") {
//                qfbLoginManager.login()
//            } else {
//                queryManager.token = BRIDGE.token
//                webView.visible = false
//                friendListModel.request("me/friends")
//            }
//        }

//        onLoginSucceeded: {
//            BRIDGE.token = token
//            queryManager.token = token
//            webView.visible = false
//            friendListModel.request("me/friends")
//        }
//    }


//    QFBFriendListModel {
//        id: friendListModel
//        queryManager: queryManager
//    }

//    ListView {
//        id: view
//        anchors.fill: parent
//        model: friendListModel
//        delegate: Rectangle {
//            width: view.width
//            height: 60

//            Image {
//                width: 40
//                height: 40
//                anchors.verticalCenter: parent.verticalCenter
//                anchors.left: parent.left; anchors.leftMargin: 20
//                source: pictureLoader.picturePath
//                asynchronous: true

//                QFBPictureLoader {
//                    id: pictureLoader
//                    queryManager: container.queryManager
//                    Component.onCompleted: request(model.data.id + "/picture")
//                }
//            }

//            Text {
//                anchors.centerIn: parent
//                font.pixelSize: 20
//                text: model.data.name
//            }

//            MouseArea {
//                anchors.fill: parent
//                onClicked: userLoader.request(model.data.id)
//            }
//        }
//    }

//    QFBUserLoader {
//        id: userLoader
//        queryManager: queryManager
//        onUserChanged: {
//            console.debug(user.id)
//            console.debug(user.name)
//            console.debug(user.firstName)
//            console.debug(user.middleName)
//            console.debug(user.lastName)
//            console.debug(user.gender)
//            console.debug(user.locale)
//            console.debug(user.link)
//            console.debug(user.username)
//            console.debug(user.bio)
//            console.debug(user.birthday)
//        }
//    }

//    WebView {
//        id: webView
//        preferredWidth: container.width
//        anchors.fill: parent
//        onUrlChanged: qfbLoginManager.checkUrl(url)
//    }



}
