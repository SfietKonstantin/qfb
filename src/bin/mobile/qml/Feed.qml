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
    height: column.height + Ui.MARGIN_DEFAULT
    property string graph
    function load() {
        model.request(container.graph)
    }

    Column {
        id: column
        width: parent.width
        spacing: Ui.MARGIN_DEFAULT
        Repeater {
            model: QFBFeedModel {
                id: model
                queryManager: QUERY_MANAGER
                validator: QFBMobilePostValidator {}
            }

            delegate: Item {
                width: container.width
                height: content.height

                QFBPostHelper {
                    id: postHelper
                    post: model.data
                }

                Post {
                    id: content
                    from: model.data.from
                    createdTime: model.data.createdTime
                    haveAdressee: postHelper.haveAdressee
                    to: postHelper.to
                    message: postHelper.message
                }
            }
        }
    }
}
