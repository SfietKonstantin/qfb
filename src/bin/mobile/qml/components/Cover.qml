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
import "../UiConstants.js" as Ui

Item {
    id: container
    property string name
    property string category
    property string coverUrl
    property bool large: false
    property QtObject queryManager
    anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
    height: !large ? (coverBackground.portrait ? Ui.BANNER_HEIGHT_PORTRAIT
                                               : Ui.BANNER_HEIGHT_LANDSCAPE)
                   : Ui.BANNER_HEIGHT_LARGE

    Rectangle {
        id: coverBackground
        property bool portrait: screen.currentOrientation == Screen.Portrait
        anchors.fill: parent
        color: Ui.THEME_COLOR_PRIMARY
        clip: true

        FacebookImage {
            id: image
            queryManager: container.queryManager
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            url: coverUrl
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.right: parent.right
            height: Ui.MARGIN_DEFAULT + Ui.FONT_SIZE_XXLARGE + Ui.MARGIN_DEFAULT
            opacity: 0.8
            gradient: Gradient {
                GradientStop {position: 0; color: "#00000000"}
                GradientStop {position: 1; color: "black"}
            }
        }

        Text {
            id: nameText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.bottom: parent.bottom
            anchors.bottomMargin: !container.large ? (container.height - nameText.height) / 2
                                                   : Ui.MARGIN_DEFAULT
            color: !theme.inverted ? Ui.FONT_COLOR_INVERTED_PRIMARY : Ui.FONT_COLOR_PRIMARY
            style: Text.Sunken
            styleColor: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            opacity: 0
            elide: Text.ElideRight
            wrapMode: Text.NoWrap
            font.pixelSize: container.large ? Ui.FONT_SIZE_XXLARGE : Ui.FONT_SIZE_LARGE
            states: [
                State {
                    name: "visible"; when: container.name != ""
                    PropertyChanges {
                        target: nameText
                        opacity: 1
                        text: container.name
                              + (container.category != "" ? (" − " + container.category) : "")
                    }
                }
            ]
            Behavior on opacity {
                NumberAnimation {duration: Ui.ANIMATION_DURATION_NORMAL}
            }
        }
    }
}
