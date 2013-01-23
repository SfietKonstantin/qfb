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
        portraitLoader.request(facebookId + "/picture")
        userLoader.request(facebookId, "fields=cover")
        postList.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }

        ToolButton {
            text: qsTr("Post something")
            onClicked: PageManagement.showFeedDialog(container.facebookId)
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
                text: container.facebookId == ME.facebookId ? qsTr("Personnal informations")
                                                            : qsTr("User informations")
                onClicked: PageManagement.addPage("UserInfoPage", {facebookId: container.facebookId,
                                                                   name: container.name,
                                                                   coverUrl: cover.coverUrl})
            }
            MenuItem {
                text: qsTr("Albums")
                onClicked: PageManagement.addPage("AlbumListPage",
                                                  {facebookId: container.facebookId,
                                                   name: container.name,
                                                   coverUrl: cover.coverUrl})
            }
            MenuItem {
                text: qsTr("Photos")
                onClicked: PageManagement.addPage("PhotoListPage",
                                                  {facebookId: container.facebookId,
                                                   name: container.name,
                                                   coverUrl: cover.coverUrl})
            }
        }
    }

    QFBUserLoader {
        id: userLoader
        queryManager: QUERY_MANAGER
        onLoaded: {
            cover.coverUrl = user.cover.source
        }
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: width
        contentHeight: cover.height + postList.height + Ui.MARGIN_DEFAULT


        Cover {
            id: cover
            queryManager: QUERY_MANAGER
            name: container.name
            large: true
        }

        Rectangle {
            id: portraitContainer
            opacity: 0
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.top: cover.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            width: portrait.width + 2 * Ui.MARGIN_XSMALL
            height: Math.min(portrait.height + 2 * Ui.MARGIN_XSMALL,
                             cover.height - 2 * Ui.MARGIN_DEFAULT)
            color: "white"

            Item {
                anchors.fill: parent
                anchors.margins: Ui.MARGIN_XSMALL
                clip: true

                Image {
                    id: portrait
                    source: portraitLoader.picturePath
                    anchors.top: parent.top
                }
            }


            QFBPictureLoader {
                id: portraitLoader
                queryManager: QUERY_MANAGER
                type: QFBPictureLoader.Normal
            }

            states: [
                State {
                    name: "visible"; when: portrait.status == Image.Ready
                    PropertyChanges {
                        target: portraitContainer
                        opacity: 1
                    }
                }
            ]
            Behavior on opacity {
                NumberAnimation {duration: Ui.ANIMATION_DURATION_NORMAL}
            }
        }

        PostList {
            id: postList
            anchors.top: cover.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            facebookId: container.facebookId
            stream: "feed"
            onShowPost: PageManagement.addPage("PostPage", {facebookId: container.facebookId,
                                                            name: container.name,
                                                            coverUrl: cover.coverUrl,
                                                            post: post})
        }
    }
}
