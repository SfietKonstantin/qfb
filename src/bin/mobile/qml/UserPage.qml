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
import "UiConstants.js" as Ui

Page {
    id: container
    property string facebookId
    property string name
    function load() {
        portraitLoader.request(facebookId + "/picture")
        userLoader.request(facebookId, "fields=cover")
        feedButton.checked = true
        feed.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PAGE_MANAGEMENT_BRIDGE.pop()
        }
        ButtonRow {
            style: TabButtonStyle {}
            TabButton {
                id: feedButton
                text: qsTr("Feed")
                onClicked: {
                    feed.load()
                }
            }
            TabButton {
                id: miscButton
                text: qsTr("Misc")
            }
        }
    }

    QFBUserLoader {
        id: userLoader
        queryManager: QUERY_MANAGER
        onLoaded: {
            banner.coverUrl = user.cover.source
        }
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        anchors.fill: parent
        contentWidth: width
        contentHeight: banner.height + (feedButton.checked ? feed.height : userMisc.height)
                       + Ui.MARGIN_DEFAULT


        Banner {
            id: banner
            name: container.name
            large: true
        }

        Rectangle {
            id: portraitContainer
            opacity: 0
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.top: banner.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            width: portrait.width + Ui.MARGIN_SMALL
            height: portrait.height + Ui.MARGIN_SMALL
            color: "white"

            Image {
                id: portrait
                source: portraitLoader.picturePath
                anchors.centerIn: parent
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

        Feed {
            id: feed
            visible: feedButton.checked
            anchors.top: banner.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            graph: container.facebookId + "/feed"
        }

        Item {
            id: userMisc
            visible: miscButton.checked
            anchors.top: banner.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            width: container.width

            height: Math.max(2 * Ui.MARGIN_DEFAULT + buttonColumn.height,
                             container.height - banner.height)

            ButtonColumn {
                exclusive: false
                anchors.centerIn: parent
                id: buttonColumn

                Button {
                    text: qsTr("Informations")
                    onClicked: PAGE_MANAGEMENT_BRIDGE.addUserInfoPage(facebookId, name,
                                                                      banner.coverUrl)
                }

                Button {
                    text: qsTr("Albums")
                    onClicked: PAGE_MANAGEMENT_BRIDGE.addAlbumListPage(facebookId, name,
                                                                       banner.coverUrl)
                }

                Button {
                    text: qsTr("Photos")
                    enabled: false
                }

                Button {
                    text: qsTr("Videos")
                    enabled: false
                }
            }
        }
    }
}
