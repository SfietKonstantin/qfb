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

Page {
    id: container
    property QtObject queryManager
    function load() {
        userLoader.request("me", "fields=name")
    }
    QtObject {
        id: d_ptr
        property string name
        property string coverUrl
    }

    QFBUserLoader {
        id: userLoader
        queryManager: container.queryManager
        onUserChanged: {
            if (d_ptr.name == "") {
                d_ptr.name = user.name
                userLoader.request("me", "fields=cover")
            } else if (d_ptr.coverUrl == "") {
                d_ptr.coverUrl = user.cover.source
            }
        }
    }

    Item {
        anchors.fill: parent

        Rectangle {
            id: coverBackground
            anchors.top: parent.top
            anchors.left: parent.left; anchors.right: parent.right
            color: "#0057AE"
            height: 0.3 * container.height

            Image {
                id: cover
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                clip: true
                asynchronous: true
                source: d_ptr.coverUrl
                opacity: 0
                states: [
                    State {
                        name: "visible"; when: cover.status == Image.Ready
                        PropertyChanges {
                            target: cover
                            opacity: 1
                        }
                    }
                ]
                Behavior on opacity {
                    NumberAnimation {duration: 300}
                }
            }
        }

        Text {
            id: nameText
            anchors.left: coverBackground.left; anchors.leftMargin: 10
            anchors.bottom: coverBackground.bottom; anchors.bottomMargin: 10
            color: "white"
            style: Text.Sunken
            styleColor: "black"
            opacity: 0
            font.pixelSize: 40
            states: [
                State {
                    name: "visible"; when: d_ptr.name != ""
                    PropertyChanges {
                        target: nameText
                        opacity: 1
                        text: d_ptr.name
                    }
                }
            ]
            Behavior on opacity {
                NumberAnimation {duration: 300}
            }
        }
    }


}
