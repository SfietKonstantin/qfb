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
import org.SfietKonstantin.qfb.mobile 4.0
import "../UiConstants.js" as Ui

Rectangle {
    id: container
    property QtObject post
    property QtObject queryManager
    property bool interactive: false
    signal clicked()
    signal resolveType(string facebookId, string name)
    anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
    anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
    height: title.height + Ui.MARGIN_DEFAULT + messageContainer.height + content.height
            + Ui.MARGIN_DEFAULT
    color: !theme.inverted ? "white" : "black"

    QFBPostHelper {
        id: postHelper
        post: container.post
    }

    BorderImage {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    Item {
        id: title
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        height: picture.height + Ui.MARGIN_DEFAULT

        FacebookPicture {
            id: picture
            anchors.verticalCenter: parent.verticalCenter
            facebookId: container.post.from.facebookId
            queryManager: container.queryManager
            pictureType: QFBPictureLoader.Square
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: picture.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right

            Label {
                id: name
                anchors.left: parent.left; anchors.right: parent.right
                font.pixelSize: Ui.FONT_SIZE_DEFAULT
                text: postHelper.header
                onLinkActivated: {
                    var strings = link.split("-")
                    container.resolveType(strings[0], strings[1])
                }
            }

            Label {
                id: date
                anchors.left: parent.left; anchors.right: parent.right
                font.pixelSize: Ui.FONT_SIZE_SMALL
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
                text: Qt.formatDateTime(container.post.createdTime, Qt.SystemLocaleShortDate)
            }
        }
    }

    Item {
        id: messageContainer
        height: postHelper.message != "" ? Ui.MARGIN_DEFAULT + message.height : 0
        anchors.top: title.bottom
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT

        Label {
            id: message
            text: postHelper.message
            anchors.top: parent.top;  anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left; anchors.right: parent.right
        }
    }

    Item {
        id: content
        anchors.top: messageContainer.bottom
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        height: contentColumn.height + Ui.MARGIN_DEFAULT

        Column {
            id: contentColumn
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Ui.MARGIN_DEFAULT

            Item {
                // There is a binding loop here (need to fix it)
                id: imageContainer
                width: contentColumn.width
                height: postImage.status != Image.Ready ? 0 : postImage.height

                FacebookImage {
                    id: postImage
                    anchors.horizontalCenter: parent.horizontalCenter
                    queryManager: container.queryManager
                    url: container.post.picture
                }
            }

            Label {
                text: container.post.name
                width: parent.width
                visible: text != ""
            }

            Label {
                text: container.post.caption
                width: parent.width
                visible: text != ""
                font.pixelSize: Ui.FONT_SIZE_SMALL
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }

            Label {
                text: container.post.description
                width: parent.width
                visible: text != ""
                font.pixelSize: Ui.FONT_SIZE_SMALL
                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            }

            Row {
                anchors.right: parent.right
                spacing: Ui.MARGIN_DEFAULT
                height: Math.max(commentsLabel.height, likesLabel.height)

                Label {
                    id: commentsLabel
                    text: qsTr("%n comments", "", container.post.comments.count)
                    font.pixelSize: Ui.FONT_SIZE_SMALL
                    color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY
                                           : Ui.FONT_COLOR_INVERTED_SECONDARY
                }

                Label {
                    id: likesLabel
                    text: qsTr("%n likes", "", container.post.likes.count)
                    font.pixelSize: Ui.FONT_SIZE_SMALL
                    color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY
                                           : Ui.FONT_COLOR_INVERTED_SECONDARY
                }
            }
        }

        MouseArea {
            id: mouseArea
            enabled: container.interactive
            anchors.fill: parent
            onClicked: container.clicked()
        }
    }
}
