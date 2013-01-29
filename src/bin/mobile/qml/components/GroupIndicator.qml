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
import "../UiConstants.js" as Ui

Item {
    id: container
    property alias text: label.text
    width: parent.width
    height: label.height

    BorderImage {
        id: headerSeparator
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: label.left; anchors.rightMargin: Ui.MARGIN_LARGE
        anchors.verticalCenter: parent.verticalCenter
        height: 2

        source: "image://theme/meegotouch-separator" + (theme.inverted ? "-inverted" : "") +
                "-background-horizontal"
        border {left: 0; top: 2; right: 0; bottom: 0}
    }

    Label {
        id: label
        font.bold: true
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_LARGE
        platformStyle: LabelStyle {
            fontPixelSize: Ui.FONT_SIZE_XXSMALL
            textColor: theme.inverted ? Ui.FONT_COLOR_INVERTED_SECONDARY :
                                        Ui.FONT_COLOR_SECONDARY
        }
    }

}


