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
import "../UiConstants.js" as Ui

Rectangle {
    id: container
    signal clicked
    property string facebookId
    property alias name: text.text
    property QtObject queryManager

    height: Ui.LIST_ITEM_HEIGHT_XXLARGE
    anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
    anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
    color: !theme.inverted ? "white" : "black"

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    Item {
        id: pictureContainer
        anchors.top: parent.top; anchors.bottom: text.top; anchors.bottomMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.right: parent.right
        opacity: !mouseArea.pressed ? 1 : 0.6

        FacebookPicture {
            id: picture
            anchors.fill: parent
            queryManager: container.queryManager
            clip: true
            pictureType: QFBPictureLoader.Album
            fillMode: Image.PreserveAspectCrop
            facebookId: container.facebookId
        }

        BusyIndicator {
            anchors.centerIn: parent
            visible: picture.loading
            running: visible
        }
    }


    Label {
        id: text
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom; anchors.bottomMargin: Ui.MARGIN_DEFAULT
        elide: Text.ElideRight
    }

    MouseArea {
        id: mouseArea
        anchors.fill: container
        onClicked: container.clicked()
    }
}
