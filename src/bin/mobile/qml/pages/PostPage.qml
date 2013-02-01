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
    function load() {
        var offset = 0
        var commentCount = container.post.comments.count
        var arguments = ""
        if (commentCount > 20) {
            offset = Math.floor(commentCount / 20) * 20
            arguments = "offset=" + offset
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
        onPostChanged: {
            container.post = postLoader.post
            POST_UPDATE_RELAY.requestUpdatePostLikesAndComments(container.post.facebookId,
                                                                container.post.likes.count,
                                                                container.post.comments.count)
        }
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
        queryManager: QUERY_MANAGER
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
                extendedView: true
                onClicked: PageManagement.addPage("LikesPage", {"facebookId": container.facebookId,
                                                                "name": container.name,
                                                                "coverUrl": container.coverUrl,
                                                                "likeListModel": likeListModel})
            }

            Item {
                width: column.width
                height: button.visible ? button.height + 2 * Ui.MARGIN_DEFAULT : 0

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
                comment: postTextArea.text
                onLoaded: {
                    container.load()
                    postTextArea.text = ""
                }
            }

            Item {
                id: commentFieldContainer
                width: column.width
                height: postTextArea.height + 2 * Ui.MARGIN_DEFAULT

                PostTextArea {
                    id: postTextArea
                    width: commentFieldContainer.width - 2 * Ui.MARGIN_DEFAULT
                    anchors.centerIn: parent
                    loading: createCommentLoader.loading
                    placeholderText: qsTr("Write a comment")
                    onClicked: createCommentLoader.request(container.post.facebookId + "/comments")
                }
            }
        }
    }
}
