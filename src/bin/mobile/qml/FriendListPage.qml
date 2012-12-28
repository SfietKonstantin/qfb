/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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
import "UiConstants.js" as Ui

Page {
    id: container
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: window.pageStack.pop()
        }
    }

    function load() {
        friendListModel.request("me/friends")
    }

    Item {
        anchors.fill: parent

        Banner {
            id: banner
            name: me.name
            coverUrl: me.coverUrl
        }

        QFBFriendListModel {
            id: friendListModel
            queryManager: QUERY_MANAGER
            autoLoadNext: true
        }

        ListView {
            clip: true
            anchors.top: banner.bottom; anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.right: parent.right
            model: friendListModel
            delegate: FriendEntry {
                facebookId: model.data.id
                name: model.data.name
            }
            ScrollDecorator {flickableItem: parent}
            cacheBuffer: Ui.LIST_ITEM_HEIGHT_DEFAULT * 5
        }
    }

}
