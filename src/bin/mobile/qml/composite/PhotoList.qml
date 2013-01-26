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
import "../UiConstants.js" as Ui
import "../components"

Item {
    id: container
    width: parent.width
    height: grid.height + Ui.MARGIN_DEFAULT
    property bool loading: model.loading
    property string graph
    property int columns
    property int count: model.count
    signal showPhoto(variant model, int index)
    function load() {
        model.request(container.graph)
    }

    Grid {
        id: grid
        width: parent.width
        columns: container.columns
        anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
        anchors.right: parent.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
        spacing: Ui.MARGIN_DEFAULT
        visible: !model.loading

        Repeater {
            id: repeater
            model: QFBPhotoListModel {
                id: model
                autoLoadNext: true
                queryManager: QUERY_MANAGER
            }

            delegate: Rectangle {
                width: (container.width - (container.columns + 1) * Ui.MARGIN_DEFAULT)
                       / container.columns
                height: width
                color: !theme.inverted ? "white" : "black"

                FacebookPicture {
                    id: picture
                    anchors.fill: parent
                    clip: true
                    pictureType: QFBPictureLoader.Normal
                    fillMode: Image.PreserveAspectCrop
                    facebookId: model.data.facebookId
                    queryManager: QUERY_MANAGER
                }

                LoadingIndicator {
                    loading: picture.loading
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: container.showPhoto(repeater.model, model.index)
                }
            }
        }
    }
}
