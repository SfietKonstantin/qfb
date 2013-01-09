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

Item
{
    id: container
    signal clicked
    property string facebookId
    property alias name: text.text

    height: Ui.LIST_ITEM_HEIGHT_DEFAULT
    width: parent.width

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    FacebookPicture {
        id: picture
        clip: true
        pictureType: QFBPictureLoader.Thumbnail
        fillMode: Image.PreserveAspectCrop
        facebookId: container.facebookId
        anchors.left: parent.left;
        anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
    }

    Label {
        id: text
        anchors.left: picture.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: indicator.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        elide: Text.ElideRight
    }

    Image {
        id: indicator
        source: "image://theme/icon-m-common-drilldown-arrow" + (theme.inverted ? "-inverse" : "")
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: container
        onClicked: container.clicked()
    }

}
