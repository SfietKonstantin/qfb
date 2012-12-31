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
        banner.loaded = false
        portraitLoader.request(facebookId + "/picture")
        userLoader.request(facebookId, "fields=cover")
        feedButton.checked = true
        feed.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: {
                window.pageStack.pop()
            }
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
                id: infoButton
                text: qsTr("Informations")
            }
        }
    }

    QFBUserLoader {
        id: userLoader
        queryManager: QUERY_MANAGER
        onLoadingChanged: {
            if (!loading) {
                if (!banner.loaded) {
                    banner.loaded = true
                    banner.coverUrl = user.cover.source
                    userLoader.request(facebookId)
                }
            }
        }
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        property bool displayFeed: true
        anchors.fill: parent
        contentWidth: width
        contentHeight: banner.height + (feedButton.checked ? feed.height : userInfo.height)
                       + Ui.MARGIN_DEFAULT


        Banner {
            id: banner
            property bool loaded: false
            name: container.name
            large: true
        }

        Rectangle {
            id: portraitContainer
            opacity: 0
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.bottom: banner.bottom; anchors.bottomMargin: Ui.MARGIN_DEFAULT
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

        UserInfo {
            id: userInfo
            visible: infoButton.checked
            anchors.top: banner.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            user: userLoader.user
        }
    }
}
