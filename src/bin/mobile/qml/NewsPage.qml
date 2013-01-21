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
    property string name
    function load() {
        banner.loaded = false
        userLoader.request("me", "fields=cover")
        feed.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PAGE_MANAGEMENT_BRIDGE.pop()
        }

        ToolButton {
            text: qsTr("Post something")
            onClicked: PAGE_MANAGEMENT_BRIDGE.showFeedDialog("me")
        }

        Item {width: 80}
    }

    QFBUserLoader {
        id: userLoader
        queryManager: QUERY_MANAGER
        onLoadingChanged: {
            if (!loading) {
                if (!banner.loaded) {
                    banner.loaded = true
                    banner.coverUrl = user.cover.source
                }
            }
        }
    }


    Item {
        anchors.top: banner.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right

        ScrollDecorator { flickableItem: flickable }
        Flickable {
            id: flickable
            anchors.fill: parent
            contentWidth: width
            contentHeight: feed.height

            Feed {
                id: feed
                facebookId: "me"
                stream: "home"
                onShowPost: PAGE_MANAGEMENT_BRIDGE.addPostPage(container.facebookId, container.name,
                                                               banner.coverUrl, post)
            }
        }
    }


    Banner {
        id: banner
        property bool loaded: false
        name: container.name
        category: qsTr("News")
    }
}
