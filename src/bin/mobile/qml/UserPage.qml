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
import "UiConstants.js" as Ui

Page {
    id: container
    property string facebookId
    property string name
    function load() {
        banner.loaded = false
        portraitLoader.request(facebookId + "/picture")
        userLoader.request(facebookId, "fields=cover")
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: window.pageStack.pop()
        }
        ButtonRow {
            style: TabButtonStyle {}
            TabButton {
                text: qsTr("Feed")
                onClicked: flickable.displayFeed = true
            }
            TabButton {
                text: qsTr("Informations")
                onClicked: flickable.displayFeed = false
            }
        }
    }

    QFBUserLoader {
        id: userLoader
        queryManager: QUERY_MANAGER
        onUserChanged: {
            if (!banner.loaded) {
                banner.loaded = true
                banner.coverUrl = user.cover.source
                userLoader.request(facebookId)
            }
        }
    }

    Flickable {
        id: flickable
        property bool displayFeed: true
        anchors.fill: parent
        contentWidth: width
        contentHeight: banner.height + portraitContainer.height / 2 + Ui.MARGIN_DEFAULT
                       + (displayFeed ? 0 : infoContainer.height)

        ScrollDecorator { flickableItem: parent }

        Banner {
            id: banner
            property bool loaded: false
            name: container.name
            large: true
        }

        Rectangle {
            id: portraitContainer
            opacity: 0
            anchors.right: parent.right; anchors.rightMargin: Ui.MARGIN_DEFAULT
            anchors.bottom: banner.bottom; anchors.bottomMargin: - height / 2
            width: portrait.width + Ui.MARGIN_SMALL
            height: portrait.height + Ui.MARGIN_SMALL
            color: "white"

            Image {
                id: portrait
                source: portraitLoader.picturePath
                anchors.centerIn: parent
            }

            QFBPictureLoader {
                id: portraitLoader
                queryManager: QUERY_MANAGER
                type: QFBPictureLoader.Normal
            }

            states: [
                State {
                    name: "visible"; when: portrait.status == Image.Ready
                    PropertyChanges {
                        target: portraitContainer
                        opacity: 1
                    }
                }
            ]
            Behavior on opacity {
                NumberAnimation {duration: Ui.ANIMATION_DURATION_NORMAL}
            }
        }

        Item {
            id: infoContainer
            visible: !flickable.displayFeed
            anchors.top: portraitContainer.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
            width: parent.width
            height: Ui.MARGIN_DEFAULT + informationsContainer.height
                    + Ui.MARGIN_DEFAULT + bioContainer.height + Ui.MARGIN_DEFAULT
                    + quotesContainer.height + Ui.MARGIN_DEFAULT

            Container {
                id: informationsContainer
                title: qsTr("Informations")
                visible: informations.text != ""
                content: Item {
                    width: parent.width
                    height: informations.height

                    Label {
                        id: informations
                        function createText() {
                            if (userLoader.user == null) {
                                return ""
                            }
                            var text = ""

                            if (userLoader.user.gender != "") {
                                text += "<b>" + qsTr("Gender") + "</b>: "
                                        + userLoader.user.gender + "<br/>"
                            }
                            text += "<br/>"

                            if(Qt.formatDate(userLoader.user.birthday, "yyyy") != "") {
                                text += "<b>" + qsTr("Birthday") + "</b>: "
                                if(Qt.formatDate(userLoader.user.birthday, "yyyy") == "1900") {
                                    text += Qt.formatDate(userLoader.user.birthday, "dd/MM")
                                } else {
                                    text += Qt.formatDate(userLoader.user.birthday, "dd/MM/yyyy")
                                }
                                text += "<br/>"
                            }

                            text += "<br/>"

                            if (userLoader.user.religion != "") {
                                text += "<b>" + qsTr("Religion") + "</b>: "
                                        + userLoader.user.religion + "<br/>"
                            }
                            if (userLoader.user.political != "") {
                                text += "<b>" + qsTr("Political view") + "</b>: "
                                        + userLoader.user.political + "<br/>"
                            }

                            text += "\n"

                            return text.trim()
                        }

                        width: parent.width
                        wrapMode: Text.WordWrap
                        text: createText()

                        Connections {
                            target: userLoader
                            onUserChanged: informations.text = informations.createText()
                        }
                    }
                }
            }

            Container {
                id: bioContainer
                anchors.top: informationsContainer.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                title: qsTr("Biography")
                visible: bio.text != ""
                content: Item {
                    width: parent.width
                    height: bio.height
                    Label {
                        id: bio
                        width: parent.width
                        wrapMode: Text.WordWrap
                        text: userLoader.user == null ? "" : userLoader.user.bio
                    }
                }
            }

            Container {
                id: quotesContainer
                anchors.top: bioContainer.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                title: qsTr("Quotes")
                visible: quotes.text != ""
                content: Item {
                    width: parent.width
                    height: quotes.height
                    Label {
                        id: quotes
                        width: parent.width
                        wrapMode: Text.WordWrap
                        text: userLoader.user == null ? "" : userLoader.user.quotes
                    }
                }
            }
        }
    }
}
