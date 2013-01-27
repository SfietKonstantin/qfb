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
        commentsModel.request(container.post.facebookId + "/comments", arguments)
        likeListModel.request(container.post.facebookId + "/likes")
        postLoader.request(container.post.facebookId)
    }

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }

        ToolIcon {
            id: likeButton
            visible: !likeListModel.loading && !likeLoader.loading
            property bool initialCheckDone: false
            property bool checked: false
            iconSource: DATA_PATH + (checked ? "un" : "") + "like-"
                        + (!theme.inverted ? "black" : "white") + ".png"
            onClicked: {
                if (checked) {
                    likeLoader.likeOperation = QFBLikeLoader.Unlike
                } else {
                    likeLoader.likeOperation = QFBLikeLoader.Like
                }
                likeLoader.request(container.post.facebookId + "/likes")
            }

            Connections {
                target: likeListModel
                onLoaded: likeButton.checked = likeListModel.contains(ME.facebookId)
            }

            Connections {
                target: likeLoader
                onLoaded: {
                    postLoader.request(container.post.facebookId)
                    likeListModel.request(container.post.facebookId + "/likes")
                }
            }
        }

        LoadingIndicator {
            anchors.centerIn: likeButton
            loading: likeListModel.loading || likeLoader.loading
        }
    }

    QFBPostLoader {
        id: postLoader
        queryManager: QUERY_MANAGER
        onPostChanged: container.post = postLoader.post
    }

    QFBLikeListModel {
        id: likeListModel
        queryManager: QUERY_MANAGER
    }

    QFBLikeLoader {
        id: likeLoader
        queryManager: QUERY_MANAGER
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
                    model: commentsModel
                    text: qsTr("Load previous comments")
                    onClicked: commentsModel.loadPrevious()
                    haveMore: commentsModel.havePrevious
                }
            }

            Repeater {
                model: QFBCommentListModel {
                    id: commentsModel
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

            QFBCreateCommentLoader {
                id: createCommentLoader
                queryManager: QUERY_MANAGER
                comment: commentField.text
                onLoaded: container.load()
            }

            Item {
                id: commentFieldContainer
                width: column.width
                height: commentField.height + Ui.MARGIN_DEFAULT

                TextArea {
                    id: commentField
                    placeholderText: qsTr("Write a comment")
                    anchors.left: parent.left; anchors.leftMargin: Ui.MARGIN_DEFAULT
                    anchors.right: commentIcon.left; anchors.rightMargin: Ui.MARGIN_DEFAULT
                    enabled: !createCommentLoader.loading
                }

                ToolIcon {
                    id: commentIcon
                    visible: !createCommentLoader.loading
                    iconId: "toolbar-new-message"
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    onClicked: createCommentLoader.request(container.post.facebookId + "/comments")
                }

                LoadingIndicator {
                    anchors.centerIn: commentIcon
                    loading: createCommentLoader.loading
                }
            }
        }
    }
}
