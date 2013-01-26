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
import com.nokia.extras 1.1
import org.SfietKonstantin.qfb.dialogs 4.0
import "../UiConstants.js" as Ui
import QtWebKit 1.0

Sheet {
    id: sheet
    property alias to: feedDialogManager.to
    function showDialog() {
        webView.url = ""
        feedDialogManager.displayDialog()
        sheet.open()
    }
    rejectButtonText: qsTr("Close dialog")
    onStatusChanged: {
        if (status == DialogStatus.Open) {
            infoBanner.show()
        } else if (status == DialogStatus.Opening) {
            sheet.visible = true
        } else if (status == DialogStatus.Closed) {
            sheet.visible = false
        }
    }

    content: Item {
        anchors.fill: parent

        Column {
            anchors.centerIn: parent
            spacing: Ui.MARGIN_DEFAULT
            visible: webView.status != WebView.Ready

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Loading")
            }

            ProgressBar {
                width: sheet.width / 2
                minimumValue: 0
                maximumValue: 1
                value: webView.progress
            }
        }


        WebView {
            id: webView
            visible: webView.status == WebView.Ready
            anchors.fill: parent
            preferredWidth: parent.width
            onUrlChanged: feedDialogManager.checkUrl(url)
        }

        InfoBanner {
            id: infoBanner
            text: qsTr("You might need to tap a field twice to display the keyboard")
        }
    }

    QFBFeedDialogManager {
        id: feedDialogManager
        clientId: CLIENT_ID
        onUrlRequested: webView.url = url
        onPostFailed: reject()
        onPostSucceeded: accept()
    }
}
