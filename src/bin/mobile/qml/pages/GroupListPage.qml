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
    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back"
            onClicked: PageManagement.pop()
        }
    }

    function load() {
        groupListModel.request("me/groups")
    }

    Item {
        anchors.fill: parent

        Cover {
            id: cover
            name: ME.name
            category: qsTr("Groups")
            coverUrl: ME.coverUrl
            queryManager: QUERY_MANAGER
        }

        QFBGroupBookmarkListModel {
            id: groupListModel
            queryManager: QUERY_MANAGER
            autoLoadNext: true
        }

        ListView {
            id: listView
            property double opacityValue: 0
            anchors.top: cover.bottom; anchors.bottom: parent.bottom
            anchors.left: parent.left; anchors.right: parent.right
            clip: true
            model: groupListModel

            delegate: GroupBookmarkEntry {
                name: model.data.name
                opacity: listView.opacityValue
                onClicked: PageManagement.addPage("GroupPage", {facebookId: model.data.facebookId,
                                                                name: model.data.name})
            }

            ScrollDecorator {flickableItem: parent}
            states: [
                State {
                    name: "loaded"; when: !groupListModel.loading
                    PropertyChanges {
                        target: listView
                        opacityValue: 1
                    }
                }
            ]

            Behavior on opacityValue {
                NumberAnimation { duration: Ui.ANIMATION_DURATION_FAST }
            }

            LoadingMessage {loading: groupListModel.loading}

            EmptyStateLabel {
                visible: !groupListModel.loading && groupListModel.count == 0
                text: qsTr("No groups")
            }
        }
    }

}
