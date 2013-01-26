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
import "../components"
import "../pagemanagement.js" as PageManagement

Page {
    id: container

    tools: ToolBarLayout {
        Item {}

        ToolIcon {
            iconId: "toolbar-view-menu"
            onClicked: menu.open()
        }
    }

    Item {
        anchors.fill: parent
        Cover {
            id: cover
            queryManager: QUERY_MANAGER
            large: screen.currentOrientation == Screen.Portrait
            name: ME.name
            coverUrl: ME.coverUrl

        }

        ListView {
            clip: true
            anchors.top: cover.bottom; anchors.bottom: parent.bottom
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
                        if (ME.name != "") {
                            newsPage.load()
                            _window_.pageStack.push(newsPage)
                        }
                    } else if (model.action == "showMe") {
                        if (ME.name != "") {
                            PageManagement.addPage("UserPage", {name: ME.name,
                                                                facebookId: ME.facebookId})
                        }

                    } else if (model.action == "showFriends") {
                        PageManagement.addPage("FriendListPage", {})
                    }
                }
            }
            ScrollDecorator {flickableItem: parent}
        }
    }

    NewsPage {
        id: newsPage
        name: ME.name
        coverUrl: ME.coverUrl
    }

    Menu {
        id: menu
        MenuLayout {
            MenuItem {
                text: qsTr("About Friends")
                onClicked: PageManagement.addPage("AboutPage", {})
            }
        }
    }
}