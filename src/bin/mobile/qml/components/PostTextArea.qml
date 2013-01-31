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
import "../UiConstants.js" as Ui

Item {
    id: container
    property bool loading
    property alias text: textArea.text
    property alias placeholderText: textArea.placeholderText
    signal clicked()
    height: textArea.height

    TextArea {
        id: textArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: button.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        enabled: !container.loading
    }

    ToolIcon {
        id: button
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        visible: !container.loading
        iconId: "toolbar-new-message"
        onClicked: container.clicked()
    }

    LoadingIndicator {
        anchors.centerIn: button
        loading: container.loading
    }
}
