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
        photoList.load()
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
        contentHeight: photoList.height

        PhotoList {
            id: photoList
            columns: 3
            graph: facebookId + "/photos"
        }
    }

    Row {
        id: loadingIndicator
        anchors.centerIn: parent
        visible: photoList.loading
        spacing: Ui.MARGIN_DEFAULT

        BusyIndicator {
            running: loadingIndicator.visible
        }

        Label {
            text: qsTr("Loading")
        }
    }
}
