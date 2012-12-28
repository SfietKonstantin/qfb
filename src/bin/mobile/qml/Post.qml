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
import "UiConstants.js" as Ui

Rectangle {
    property QtObject from
    property bool haveAdressee: false
    property QtObject to
    property date createdTime
    property alias message: message.text
    property alias content: content.children
    anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
    anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
    height: visible ? Ui.MARGIN_DEFAULT + title.height + Ui.MARGIN_DEFAULT + message.height
                      + Ui.MARGIN_DEFAULT + content.height + Ui.MARGIN_DEFAULT
                    : 0

    Item {
        id: title
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        height: picture.height + Ui.MARGIN_DEFAULT

        FacebookPicture {
            id: picture
            queryManager: QUERY_MANAGER
            anchors.verticalCenter: parent.verticalCenter
            facebookId: from.id
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
                text: from.name + (haveAdressee ? " > " + to.name : "")
                elide: Text.ElideRight
                wrapMode: Text.NoWrap
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

    Label {
        id: message
        anchors.top: title.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
    }

    Item {
        id: content
        anchors.top: message.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        height: childrenRect.height
    }
}
