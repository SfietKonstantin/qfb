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
    property string coverUrl
    property QtObject post
    property int offset: 0
    function load() {
        container.offset = 0
        var commentCount = container.post.comments.count
        var arguments = ""
        if (commentCount > 20) {
            container.offset = Math.floor(commentCount / 20) * 20
            arguments = "offset=" + container.offset
        }
        model.request(container.post.facebookId + "/comments", arguments)
        postLoader.request(container.post.facebookId)
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PAGE_MANAGEMENT_BRIDGE.pop()
        }
    }

    QFBPostLoader {
        id: postLoader
        onPostChanged: container.post = post
    }

    Banner {
        id: banner
        name: container.name
        category: qsTr("Post")
        coverUrl: container.coverUrl
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        clip: true
        anchors.top: banner.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        contentWidth: flickable.width
        contentHeight: column.height

        Column {
            id: column
            anchors.top: parent.top
            anchors.left: parent.left; anchors.right: parent.right

            Post {
                id: post
                post: container.post
            }

            Item {
                width: column.width
                height: loadPreviousCommentButton.height + 2 * Ui.MARGIN_DEFAULT
                visible: model.havePrevious

                BusyIndicator {
                    anchors.verticalCenter: loadPreviousCommentButton.verticalCenter
                    anchors.right: loadPreviousCommentButton.left
                    anchors.rightMargin: Ui.MARGIN_DEFAULT
                    visible: model.loading
                    running: visible
                }

                Button {
                    id: loadPreviousCommentButton
                    enabled: !model.loading
                    anchors.centerIn: parent
                    text: !model.loading ? qsTr("Load previous comments") : qsTr("Loading")
                    onClicked: model.loadPrevious()
                }
            }

            Repeater {
                model: QFBCommentListModel {
                    id: model
                    queryManager: QUERY_MANAGER
                }
                delegate: Item {
                    width: column.width
                    height: comment.height

                    CommentEntry {
                        id: comment
                        comment: model.data
                    }
                }
            }
        }
    }
}
