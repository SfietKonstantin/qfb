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
import "../UiConstants.js" as Ui
import "../pagemanagement.js" as PageManagement
import "../components"

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
            onClicked: PageManagement.pop()
        }
    }

    QFBPostLoader {
        id: postLoader
        onPostChanged: container.post = post
    }

    Cover {
        id: cover
        name: container.name
        category: qsTr("Post")
        coverUrl: container.coverUrl
    }

    ScrollDecorator { flickableItem: flickable }
    Flickable {
        id: flickable
        clip: true
        anchors.top: cover.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        contentWidth: flickable.width
        contentHeight: column.height

        Column {
            id: column
            anchors.top: parent.top
            anchors.left: parent.left; anchors.right: parent.right

            Post {
                id: post
                queryManager: QUERY_MANAGER
                post: container.post
            }

            Item {
                width: column.width
                height: button.height + Ui.MARGIN_DEFAULT
                        + (button.visible ? Ui.MARGIN_DEFAULT : 0)

                LoadingButton {
                    id: button
                    anchors.centerIn: parent
                    model: model
                    text: qsTr("Load previous comments")
                    onClicked: model.loadPrevious()
                    haveMore: model.havePrevious
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
                        queryManager: QUERY_MANAGER
                    }
                }
            }
        }
    }
}
