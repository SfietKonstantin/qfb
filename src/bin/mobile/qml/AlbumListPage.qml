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
    property string coverUrl
    function load() {
        albumList.load()
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PAGE_MANAGEMENT_BRIDGE.pop()
        }
    }


    Banner {
        id: banner
        name: container.name
        coverUrl: container.coverUrl
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        clip: true
        anchors.top: banner.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom
        anchors.left: parent.left; anchors.right: parent.right
        contentWidth: container.width
        contentHeight: albumList.height

        AlbumList {
            id: albumList
            graph: facebookId + "/albums"
            onShowAlbum: PAGE_MANAGEMENT_BRIDGE.addPhotoListPage(facebookId, container.name,
                                                                 container.coverUrl)
        }
    }

    Label {
        anchors.fill: flickable
        visible: !albumList.loading && albumList.count == 0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: Ui.FONT_SIZE_XXLARGE
        color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
        text: qsTr("No albums")
    }
}
