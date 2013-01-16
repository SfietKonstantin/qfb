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
import org.SfietKonstantin.qfb.mobile 4.0
import "UiConstants.js" as Ui

Item {
    id: container
    width: parent.width
    height: column.height + Ui.MARGIN_DEFAULT + (model.haveNext ? button.height + Ui.MARGIN_DEFAULT
                                                                : 0)
    property bool loading: model.loading
    property string graph
    property int count: model.count
    signal showAlbum(string facebookId)
    function load() {
        model.request(container.graph)
    }

    Column {
        id: column
        width: parent.width
        spacing: Ui.MARGIN_DEFAULT

        Repeater {
            model: QFBAlbumListModel {
                id: model
                queryManager: QUERY_MANAGER
            }

            delegate: Item {
                width: container.width
                height: content.height

                AlbumEntry {
                    id: content
                    facebookId: model.data.facebookId
                    name: model.data.name
                    onClicked: container.showAlbum(model.data.facebookId)
                }
            }
        }
    }

    BusyIndicator {
        anchors.verticalCenter: button.verticalCenter
        anchors.right: button.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        visible: model.loading
        running: visible
    }

    Button {
        id: button
        visible: (model.haveNext && model.count > 0) || model.loading
        anchors.top: column.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.horizontalCenter: parent.horizontalCenter
        text: !model.loading ? qsTr("Load more") : qsTr("Loading")
        enabled: !model.loading
        onClicked: model.loadNext()
    }
}
