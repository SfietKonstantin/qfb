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
import "../components"
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

    ListModel {
        id: model
        ListElement {
            icon: "sfiet_konstantin.jpg"
            category: "Main developer"
            name: "Lucien XU"
            nickname: "Sfiet_Konstantin"
            description: "Main developer"
            twitter: "https://twitter.com/SfietKonstantin"
            website: ""
        }
        ListElement {
            icon: "aniket.jpg"
            category: "Thanks to"
            name: "Aniket Vasishth"
            nickname: ""
            description: "Icons master"
            twitter: "https://twitter.com/LogonAniket"
            website: ""
        }
    }

    Label {
        id: title
        anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        font.pixelSize: Ui.FONT_SIZE_XXLARGE
        font.bold: true
        text: qsTr("Developers")
    }

    ListView {
        id: view
        clip: true
        anchors.top: title.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        model: model
        section.property: "category"
        section.delegate: GroupIndicator {
            text: section
        }

        delegate: Item {
            width: view.width
            height: column.height + 2 * Ui.MARGIN_DEFAULT

            Image {
                id: icon
                width: Ui.ICON_SIZE_XLARGE; height: Ui.ICON_SIZE_XLARGE
                anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                anchors.verticalCenter: parent.verticalCenter
                source: model.icon != "" ? DATA_PATH + model.icon : ""
            }

            Column {
                id: column
                anchors.top: parent.top; anchors.topMargin: Ui.MARGIN_DEFAULT
                anchors.left: icon.right; anchors.leftMargin: Ui.MARGIN_DEFAULT
                spacing: Ui.MARGIN_XSMALL
                Label {
                    font.pixelSize: Ui.FONT_SIZE_LARGE
                    text: model.name + (model.nickname != "" ? " (" + model.nickname + ")" : "")
                }

                Label {
                    text: model.description
                }

                Row {
                    Button {
                        iconSource: "image://theme/icon-s-service-twitter"
                        platformStyle: ButtonStyle {
                            buttonWidth: 51
                            buttonHeight: 51
                        }
                        onClicked: Qt.openUrlExternally(model.twitter)
                    }
                }
            }


        }
    }


}
