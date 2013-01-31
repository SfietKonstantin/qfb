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
import org.SfietKonstantin.qfb.mobile 4.0
import "../UiConstants.js" as Ui
import "../pagemanagement.js" as PageManagement
import "../composite"
import "../components"

Page {
    id: container
    property string facebookId
    property string name
    function load() {
        postList.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }

        ToolIcon {
            iconId: "toolbar-view-menu"
            onClicked: menu.open()
        }
    }

    Menu {
        id: menu
        MenuLayout {
            MenuItem {
                text: qsTr("Group informations")
                enabled: false
            }
            MenuItem {
                text: qsTr("Events")
                enabled: false
            }
            MenuItem {
                text: qsTr("Photos")
                enabled: false
            }
        }
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: width
        contentHeight: cover.height + postContainer.height + postList.height + 2 * Ui.MARGIN_DEFAULT


        Cover {
            id: cover
            queryManager: QUERY_MANAGER
            name: container.name
            large: true
        }

        Item {
            id: postContainer
            anchors.top: cover.bottom
            width: parent.width
            height: postTextArea.height + 2 * Ui.MARGIN_DEFAULT

            PostTextArea {
                id: postTextArea
                width: postContainer.width - 2 * Ui.MARGIN_DEFAULT
                anchors.centerIn: parent
                placeholderText: qsTr("Post something")
                loading: createPostLoader.loading
                onClicked: createPostLoader.request(container.facebookId + "/feed")
            }

            QFBCreatePostLoader {
                id: createPostLoader
                queryManager: QUERY_MANAGER
                message: postTextArea.text
                onLoaded: container.load()
            }
        }

        PostList {
            id: postList
            anchors.top: postContainer.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            facebookId: container.facebookId
            stream: "feed"
            onShowPost: PageManagement.addPage("PostPage", {facebookId: container.facebookId,
                                                            name: container.name,
                                                            coverUrl: "", post: post})
        }
    }
}
