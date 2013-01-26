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
import "../pagemanagement.js" as PageManagement
import "../components"

Page {
    id: container
    property QtObject model
    function setPosition(index) {
        view.positionViewAtIndex(index, ListView.Contain)
    }

    Rectangle {
        anchors.fill: parent
        color: "black"
    }

    ListView {
        id: view
        clip: true
        anchors.fill: parent
        orientation: ListView.Horizontal
        model: container.model
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        delegate: Flickable {
            id: flickable
            interactive: image.scale != 1
            width: view.width
            height: view.height
            contentWidth: view.width
            contentHeight: view.height
            clip: true

            PinchArea {
                id: pinchArea
                width: Math.max(flickable.contentWidth, flickable.width)
                height: Math.max(flickable.contentHeight, flickable.height)
                pinch.minimumScale: 1
                pinch.maximumScale: 5
                pinch.target: image

                onPinchUpdated: {
                    var scaledWidth = view.width * image.scale
                    var scaledHeight = view.height * image.scale
                    var scaledPaintedWidth = image.paintedWidth * image.scale
                    var scaledPaintedHeight = image.paintedHeight * image.scale
                    flickable.contentX += pinch.previousCenter.x - pinch.center.x
                    flickable.contentY += pinch.previousCenter.y - pinch.center.y
                    if (scaledPaintedWidth < view.height || scaledPaintedHeight < view.height) {
                        flickable.resizeContent(scaledWidth, scaledHeight, pinch.center)
                    } else {
                        flickable.resizeContent(scaledPaintedWidth, scaledPaintedHeight,
                                                pinch.center)
                    }
                }

                onPinchFinished: {
                    flickable.returnToBounds()
                }

            }

            Item {
                width: flickable.contentWidth
                height: flickable.contentHeight

                FacebookImage {
                    id: image
                    anchors.centerIn: parent
                    width: view.width - 2 * Ui.MARGIN_XSMALL
                    height: view.height - 2 * Ui.MARGIN_XSMALL
                    queryManager: QUERY_MANAGER
                    source: model.data.source
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    onScaleChanged: {
                        view.interactive = (scale == 1)
                    }
                }
            }

            LoadingIndicator {
                loading: image.status != Image.Ready
                inverted: true
            }
        }
    }

    Item {
        id: falseToolbar
        opacity: window.pageStack.busy ? 0 : 1
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 70

        ToolIcon {
            iconId: "toolbar-back"
            anchors.verticalCenter: parent.verticalCenter
            onClicked: PageManagement.pop()
        }

        Behavior on opacity {
            NumberAnimation {duration: Ui.ANIMATION_DURATION_XFAST}
        }
    }
}
