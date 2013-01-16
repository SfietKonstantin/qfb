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

Item {
    id: container
    signal clicked
    property QtObject comment

    width: parent.width
    height: content.height + 2 * Ui.MARGIN_DEFAULT

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    FacebookPicture {
        id: picture
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        facebookId: container.comment.from.facebookId
        pictureType: QFBPictureLoader.Square
    }

    Column {
        id: content
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: picture.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT

        Label {
            id: name
            width: content.width
            font.pixelSize: Ui.FONT_SIZE_SMALL
            text: container.comment.from.name
        }

        Label {
            id: message
            width: content.width
            text: container.comment.message
        }

    }

    MouseArea {
        id: mouseArea
        anchors.fill: container
        onClicked: container.clicked()
    }
}
