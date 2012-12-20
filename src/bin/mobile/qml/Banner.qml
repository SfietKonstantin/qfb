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

Item {
    id: container
    property QtObject queryManager
    function load(graph) {
        d_ptr.graph = graph
        userLoader.request(d_ptr.graph, "fields=name")
    }

    QtObject {
        id: d_ptr
        property string graph
        property string name
        property string coverUrl
    }

    QFBUserLoader {
        id: userLoader
        queryManager: container.queryManager
        onUserChanged: {
            if (d_ptr.name == "") {
                d_ptr.name = user.name
                userLoader.request(d_ptr.graph, "fields=cover")
            } else if (d_ptr.coverUrl == "") {
                d_ptr.coverUrl = user.cover.source
            }
        }
    }

    Rectangle {
        id: coverBackground
        anchors.fill: parent
        color: "#0057AE"

        QFBImageLoader {
            id: coverImageLoader
            queryManager: container.queryManager

        }

        Connections {
            target: d_ptr
            onCoverUrlChanged: coverImageLoader.request(d_ptr.coverUrl)
        }

        Image {
            id: cover
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            clip: true
            asynchronous: true
            source: coverImageLoader.imagePath
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
                NumberAnimation {duration: Ui.ANIMATION_DURATION_NORMAL}
            }
        }

        Text {
            id: nameText
            anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
            anchors.bottom: parent.bottom; anchors.bottomMargin: Ui.MARGIN_DEFAULT
            color: !theme.inverted ? Ui.FONT_COLOR_INVERTED_PRIMARY : Ui.FONT_COLOR_PRIMARY
            style: Text.Sunken
            styleColor: !theme.inverted ? Ui.FONT_COLOR_SECONDARY : Ui.FONT_COLOR_INVERTED_SECONDARY
            opacity: 0
            font.pixelSize: Ui.FONT_SIZE_XXLARGE
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
                NumberAnimation {duration: Ui.ANIMATION_DURATION_NORMAL}
            }
        }
    }
}
