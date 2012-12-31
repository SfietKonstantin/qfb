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

Rectangle {
    id: container
    property string header
    property QtObject from
    property date createdTime
    property string message
    property string picture
    property string name
    property string caption
    property string description
    anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
    anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
    height: childrenRect.height + 2 * Ui.MARGIN_DEFAULT
    color: !theme.inverted ? "white" : "black"

    Item {
        id: title
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        height: picture.height + Ui.MARGIN_DEFAULT

        FacebookPicture {
            id: picture
            anchors.verticalCenter: parent.verticalCenter
            facebookId: from.facebookId
        }

        Item {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: picture.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right
            height: Ui.FONT_SIZE_DEFAULT + Ui.MARGIN_DEFAULT + Ui.FONT_SIZE_SMALL

            Label {
                id: name
                anchors.top: parent.top
                anchors.left: parent.left; anchors.right: parent.right
                font.pixelSize: Ui.FONT_SIZE_DEFAULT
                text: header
                elide: Text.ElideRight
                wrapMode: Text.NoWrap
                onLinkActivated: PAGE_MANAGEMENT_BRIDGE.addUserPage(link)
            }

            Label {
                id: date
                anchors.bottom: parent.bottom
                anchors.left: parent.left; anchors.right: parent.right
                font.pixelSize: Ui.FONT_SIZE_SMALL
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
                text: Qt.formatDateTime(createdTime, Qt.SystemLocaleShortDate)
            }
        }
    }

    Item {
        id: messageContainer
        height: container.message != "" ? Ui.MARGIN_DEFAULT + message.height : 0
        anchors.top: title.bottom
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT

        Label {
            id: message
            text: container.message
            anchors.top: parent.top;  anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.right: parent.right
        }
    }

    Item {
        id: content
        property bool valid: container.picture != "" || container.name != ""
                             || container.caption != "" || container.description != ""
        anchors.top: messageContainer.bottom
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        height: valid ? contentColumn.height + Ui.MARGIN_DEFAULT : 0

        Column {
            id: contentColumn
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Ui.MARGIN_DEFAULT

            FacebookImage {
                id: postImage
                anchors.horizontalCenter: parent.horizontalCenter
                url: container.picture
            }

            Label {
                text: container.name
                width: parent.width
                visible: text != ""
            }

            Label {
                text: container.caption
                width: parent.width
                visible: text != ""
                font.pixelSize: Ui.FONT_SIZE_SMALL
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }

            Label {
                text: container.description
                width: parent.width
                visible: text != ""
                font.pixelSize: Ui.FONT_SIZE_SMALL
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }
        }
    }
}
