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
    property bool extendedView: false
    property bool interactive: false
    signal clicked()
    signal callWebBrowser(string url)
    signal resolveType(string facebookId, string name)
    function reactToLink(link) {
        var strings = link.split("----")
        if (strings[0] == "user") {
            container.resolveType(strings[1], strings[2])
        } else if (strings[0] == "url") {
            callWebBrowser(strings[1])
        }
    }
    anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
    anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
    height: childrenRect.height + Ui.MARGIN_DEFAULT
    color: !theme.inverted ? "white" : "black"

    QFBPostHelper {
        id: postHelper
        post: container.post
        fancy: !container.extendedView
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
                onLinkActivated: reactToLink(link)
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
            textFormat: Text.RichText
            onLinkActivated: reactToLink(link)
        }
    }

    Item {
        id: content
        anchors.top: messageContainer.bottom
        anchors.left: parent.left; anchors.right: parent.right
        height: childrenRect.height + Ui.MARGIN_DEFAULT

        Separator {
            id: separator
            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
            anchors.leftMargin: 0; anchors.rightMargin: 0
        }


        Item {
            anchors.top: separator.bottom; anchors.left: parent.left; anchors.right: parent.right
            height: Ui.LIST_ITEM_HEIGHT_SMALL

            BorderImage {
                id: background
                anchors.fill: parent
                visible: mouseArea.pressed
                source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                        "-background-pressed-center"
            }

            Label {
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("%n likes", "", container.post.likes.count)
                      + (!container.extendedView ?  ", " + qsTr("%n comments", "",
                                                                container.post.comments.count)
                                                 : "")
            }

            Image {
                id: indicator
                visible: !container.extendedView || container.post.likes.count != 0
                source: "image://theme/icon-m-common-drilldown-arrow" +
                        (theme.inverted ? "-inverse" : "")
                anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                id: mouseArea
                onClicked: container.clicked()
                anchors.fill: parent
                enabled: !container.extendedView || container.post.likes.count != 0
            }
        }

    }

//    Item {
//        id: content
//        anchors.top: messageContainer.bottom
//        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
//        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
//        height: contentColumn.height + Ui.MARGIN_DEFAULT

//        Column {
//            id: contentColumn
//            anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
//            anchors.left: parent.left
//            anchors.right: parent.right
//            spacing: Ui.MARGIN_DEFAULT

//            Item {
//                // There is a binding loop here (need to fix it)
//                id: imageContainer
//                width: contentColumn.width
//                height: postImage.status != Image.Ready ? 0 : postImage.height

//                FacebookImage {
//                    id: postImage
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    queryManager: container.queryManager
//                    url: container.post.picture
//                }
//            }

//            Label {
//                text: container.post.name
//                width: parent.width
//                visible: text != ""
//            }

//            Label {
//                text: container.post.caption
//                width: parent.width
//                visible: text != ""
//                font.pixelSize: Ui.FONT_SIZE_SMALL
//                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
//            }

//            Label {
//                text: container.post.description
//                width: parent.width
//                visible: text != ""
//                font.pixelSize: Ui.FONT_SIZE_SMALL
//                color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
//            }

//            Row {
//                anchors.right: parent.right
//                spacing: Ui.MARGIN_DEFAULT
//                height: Math.max(commentsLabel.height, likesLabel.height)

//                Label {
//                    id: commentsLabel
//                    text: qsTr("%n comments", "", container.post.comments.count)
//                    font.pixelSize: Ui.FONT_SIZE_SMALL
//                    color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY
//                                           : Ui.FONT_COLOR_INVERTED_SECONDARY
//                }

//                Label {
//                    id: likesLabel
//                    text: qsTr("%n likes", "", container.post.likes.count)
//                    font.pixelSize: Ui.FONT_SIZE_SMALL
//                    color: !theme.inverted ? Ui.FONT_COLOR_SECONDARY
//                                           : Ui.FONT_COLOR_INVERTED_SECONDARY
//                }
//            }
//        }

//        MouseArea {
//            id: mouseArea
//            enabled: container.interactive
//            anchors.fill: parent
//            onClicked: container.clicked()
//        }
//    }
}
