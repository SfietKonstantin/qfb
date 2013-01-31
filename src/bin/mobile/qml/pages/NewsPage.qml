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
import "../components"
import "../composite"

Page {
    id: container
    property string name
    property string coverUrl
    function load() {
        postList.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }

        ToolButton {
            text: qsTr("Post something")
            onClicked: PageManagement.showFeedDialog(ME.facebookId)
        }

        Item {width: 80}
    }

    Cover {
        id: cover
        name: container.name
        coverUrl: container.coverUrl
        category: qsTr("News")
        queryManager: QUERY_MANAGER
    }

    Item {
        anchors.top: cover.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right

        ScrollDecorator { flickableItem: flickable }
        Flickable {
            id: flickable
            anchors.fill: parent
            clip: true
            contentWidth: width
            contentHeight: postList.height

            PostList {
                id: postList
                facebookId: ME.facebookId
                stream: "home"
                onShowPost: PageManagement.addPage("PostPage", {facebookId: container.facebookId,
                                                                name: container.name,
                                                                coverUrl: coverUrl,
                                                                post: post})
            }
        }

        EmptyStateLabel {
            visible: postList.count == 0 && !postList.loading
            text: qsTr("No news")
        }
    }
}
