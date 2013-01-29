/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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
    property QtObject likeListModel

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }
    }

    function load() {}

    Item {
        anchors.fill: parent

        Cover {
            id: cover
            name: container.name
            category: qsTr("Likes")
            coverUrl: container.coverUrl
            queryManager: QUERY_MANAGER
        }

        Flickable {
            anchors.top: cover.bottom; anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.right: parent.right

            Column {
                id: column
                width: parent.width

                Repeater {
                    model: container.likeListModel
                    delegate: FriendEntry {
                        facebookId: model.data.facebookId
                        name: model.data.name
                        queryManager: QUERY_MANAGER
                        onClicked: PageManagement.addPage("UserPage",
                                                          {facebookId: model.data.facebookId,
                                                           name: model.data.name})
                    }
                }
            }

            LoadingButton {
                anchors.top: column.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
                model: likeListModel
                text: qsTr("Load more")
                haveMore: model.haveNext
                onClicked: model.loadNext()
            }
        }

//        ListView {
//            id: listView
//            property double opacityValue: 0
//            anchors.top: cover.bottom; anchors.bottom: parent.bottom
//            anchors.left: parent.left; anchors.right: parent.right
//            clip: true
//            model: friendListModel
//            delegate: FriendEntry {
//                facebookId: model.data.facebookId
//                name: model.data.name
//                queryManager: QUERY_MANAGER
//                opacity: listView.opacityValue
//                onClicked: PageManagement.addPage("UserPage", {facebookId: model.data.facebookId,
//                                                               name: model.data.name})
//            }
//            section.property: "name"
//            section.criteria : ViewSection.FirstCharacter
//            section.delegate: GroupIndicator {
//                text: section
//            }

//            ScrollDecorator {flickableItem: parent}
//            cacheBuffer: Ui.LIST_ITEM_HEIGHT_DEFAULT * 5
//            states: [
//                State {
//                    name: "loaded"; when: !friendListModel.loading
//                    PropertyChanges {
//                        target: listView
//                        opacityValue: 1
//                    }
//                }
//            ]

//            Behavior on opacityValue {
//                NumberAnimation { duration: Ui.ANIMATION_DURATION_FAST }
//            }

//            LoadingMessage {loading: friendListModel.loading}

//            EmptyStateLabel {
//                visible: !friendListModel.loading && friendListModel.count == 0
//                text: qsTr("No friends")
//            }
//        }
    }

}
