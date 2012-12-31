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
import com.nokia.meego 1.0
import org.SfietKonstantin.qfb 4.0

Page {
    id: container

    Item {
        anchors.fill: parent
        Banner {
            id: banner
            large: true
            name: me.name
            coverUrl: me.coverUrl
        }

        ListView {
            clip: true
            anchors.top: banner.bottom; anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.right: parent.right
            model: ListModel {
                ListElement {
                    text: "News feed"
                    action: "showNews"
                }
                ListElement {
                    text: "Me"
                    action: "showMe"
                }
                ListElement {
                    text: "Friends"
                    action: "showFriends"
                }
            }
            delegate: ClickableEntry {
                text: model.text
                onClicked: {
                    if (model.action == "showNews") {
                        if (me.name != "") {
                            var newsPage = window.pageStack.push(Qt.resolvedUrl("NewsPage.qml"),
                                                                 {"facebookId": "me",
                                                                  "name": me.name})
                            newsPage.load()
                        }
                    } else if (model.action == "showMe") {
                        if (me.name != "") {
                            var mePage = window.pageStack.push(Qt.resolvedUrl("UserPage.qml"),
                                                               {"facebookId": "me",
                                                                "name": me.name})
                            mePage.load()
                        }

                    } else if (model.action == "showFriends") {
                        friendListPage.load()
                        window.pageStack.push(friendListPage)
                    }
                }
            }
            ScrollDecorator {flickableItem: parent}
        }
    }

    FriendListPage {
        id: friendListPage
    }
}
