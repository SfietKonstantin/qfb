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
import "../pagemanagement.js" as PageManagement
import "../UiConstants.js" as Ui

Page {
    id: container
    orientationLock: PageOrientation.LockPortrait
    function load() {}

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }
    }

    Image {
        id: icon
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.horizontalCenter: parent.horizontalCenter
        source: DATA_PATH + "/friends.png"
        smooth: true
        width: 128
        height: 128
    }

    Label {
        id: title
        anchors.top: icon.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Ui.FONT_SIZE_XXLARGE
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        text: qsTr("Friends")
    }

    Label {
        id: version
        anchors.top: title.bottom; anchors.topMargin: Ui.MARGIN_SMALL
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Ui.FONT_SIZE_SMALL
        text: qsTr("Version") + " " + VERSION_MAJOR + "." + VERSION_MINOR + "." + VERSION_PATCH
              + ", powered by QFB."
    }

    Label {
        id: info
        anchors.top: version.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
        text: qsTr("Friends is a Facebook client that tries to provide the best experience for \
the user. It is an Open Source software, meaning that it can me modified and enhanced by \
anybody. If you like Friends, please consider a donation for supporting the developers. \
This donation will help maintaining the software, and keeping it status of Open Source software.")
    }


    ButtonColumn {
        anchors.bottom: parent.bottom; anchors.bottomMargin: Ui.MARGIN_DEFAULT
        anchors.horizontalCenter: parent.horizontalCenter
        exclusive: false

        Button {
            iconSource: "image://theme/icon-l-facebook-main-view"
            text: qsTr("Facebook page")
            onClicked: Qt.openUrlExternally(FACEBOOK_PAGE)
        }

        Button {
            iconSource: "image://theme/icon-m-messaging-smiley-heart"
            text: qsTr("Donate")
            onClicked: Qt.openUrlExternally(PAYPAL_DONATE)
        }

        Button {
            iconSource: DATA_PATH + "developers.png"
            text: qsTr("Developers")
            onClicked: PageManagement.addPage("DevelopersPage", {})
        }
    }
}
