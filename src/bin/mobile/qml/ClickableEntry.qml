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

// This item is an entry of a list that
// has some features.
//
// Since it is an entry of a list, it has
// a text. An icon can also be add, as
// well as a subtext, that appears under
// the text, and an indicator, that can
// indicates a drill down or a combo-box
// for example.
//
// This is done by setting icon, text,
// subText and indicatorIcon.
//
// Width and height do not need to be set for
// this item.
Item
{
    id: container
    signal clicked
    signal pressAndHold
    property string icon: ""
    property alias text: mainText.text
    property alias subText: subText.text
    property string indicatorIcon: "icon-m-common-drilldown-arrow" +
                                   (theme.inverted ? "-inverse" : "")

    height: Ui.LIST_ITEM_HEIGHT_DEFAULT
    width: parent.width

    BorderImage
    {
        id: background
        anchors.fill: parent
        visible: mouseArea.pressed
        source: "image://theme/meegotouch-list" + (theme.inverted ? "-inverted" : "") +
                "-background-pressed-center"
    }

    Image
    {
        id: icon
        anchors.left: parent.left;
        anchors.leftMargin: container.icon != "" ? Ui.MARGIN_DEFAULT : 0
        anchors.verticalCenter: parent.verticalCenter
        width: container.icon != "" ? Ui.ICON_SIZE_LARGE : 0
        height: Ui.ICON_SIZE_LARGE
        visible: container.icon != ""
        smooth: true
        source: container.icon != "" ? container.icon : ""
        asynchronous: true
        opacity: 0
        states: State {
            name: "visible"; when: status == Image.Ready
            PropertyChanges {
                target: icon
                opacity: 1
            }
        }
        Behavior on opacity {
            NumberAnimation {duration: Ui.ANIMATION_DURATION_FAST}
        }
    }

    Item {
        id: textContainer
        anchors.left: icon.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: indicator.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
        height: subText.text != "" ? mainText.height + Ui.MARGIN_XSMALL + subText.height :
                                         mainText.height

        Label {
            id: mainText
            anchors.left: parent.left; anchors.right: parent.right
            platformStyle: LabelStyle {
                fontPixelSize: Ui.FONT_SIZE_MLARGE
            }
        }

        Label {
            id: subText
            anchors.top: mainText.bottom; anchors.topMargin: Ui.MARGIN_XSMALL
            anchors.left: parent.left; anchors.right: parent.right
            elide: Text.ElideRight
            platformStyle: LabelStyle {
                fontPixelSize: Ui.FONT_SIZE_SMALL
                textColor: theme.inverted ? Ui.FONT_COLOR_INVERTED_SECONDARY :
                                            Ui.FONT_COLOR_SECONDARY
            }
        }
    }



    Image {
        id: indicator
        source: container.indicatorIcon != "" ? "image://theme/" + container.indicatorIcon : ""
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea {
        id: mouseArea
        anchors.fill: container
        onClicked: container.clicked()
        onPressAndHold: container.pressAndHold()
    }
}
