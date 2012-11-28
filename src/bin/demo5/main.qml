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

import QtQuick 2.0
import org.SfietKonstantin.qfb 5.0
import org.SfietKonstantin.qfb.login 5.0

Item {
    id: container
    width: 480
    height: 600

    QFBLoginManager {
        id: qfbLoginManager
        clientId: "390204064393625"
        permissions: QFBLoginManager.ReadFriendList + QFBLoginManager.ReadInsights
        uiType: QFBLoginManager.Mobile
        onUrlRequested: webView.url = url
        Component.onCompleted: {
            if (BRIDGE.token == "") {
                qfbLoginManager.login()
            } else {
                queryManager.token = BRIDGE.token
                console.debug("Using existing token:" + BRIDGE.token)
                queryManager.queryFriends("me/friends")
            }
        }

        onLoginSucceeded: {
            BRIDGE.token = token
            queryManager.token = token
            webView.visible = false
        }
    }

    QFBQueryManager {
        id: queryManager
    }

//    WebView {
//        id: webView
//        preferredWidth: container.width
//        anchors.fill: parent
//        onUrlChanged: qfbLoginManager.checkUrl(url)
//    }
}
