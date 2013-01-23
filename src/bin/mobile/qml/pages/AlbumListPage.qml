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
    property string coverUrl
    function load() {
        albumList.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }
    }


    Cover {
        id: cover
        name: container.name
        category: qsTr("Albums")
        coverUrl: container.coverUrl
    }


    Item {
        id: content
        anchors.top: cover.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right

        ScrollDecorator { flickableItem: flickable }
        Flickable {
            id: flickable
            anchors.fill: parent
            clip: true
            contentWidth: container.width
            contentHeight: albumList.height

            AlbumList {
                id: albumList
                graph: facebookId + "/albums"
                onShowAlbum: PageManagement.addPage("PhotoListPage", {facebookId: facebookId,
                                                                      name: container.name,
                                                                      coverUrl: container.coverUrl})
            }
        }

        EmptyStateLabel {
            visible: !albumList.loading && albumList.count == 0
            text: qsTr("No albums")
        }
    }


}
