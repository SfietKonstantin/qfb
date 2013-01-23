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
import org.SfietKonstantin.qfb.mobile 4.0
import "../UiConstants.js" as Ui
import "../components"

Item {
    id: container
    property QtObject user
    property alias valid: userInfoHelper.valid
    width: parent.width
    height: Ui.MARGIN_DEFAULT + informationsContainer.height
            + Ui.MARGIN_DEFAULT + bioContainer.height + Ui.MARGIN_DEFAULT
            + quotesContainer.height + Ui.MARGIN_DEFAULT

    QFBUserInfoHelper {
        id: userInfoHelper
        user: container.user
    }

    Container {
        id: informationsContainer
        title: qsTr("Informations")
        visible: informations.text != ""
        content: Item {
            width: parent.width
            height: informations.height

            Label {
                id: informations
                width: parent.width
                wrapMode: Text.WordWrap
                text: userInfoHelper.formattedInformations
            }
        }
    }

    Container {
        id: bioContainer
        anchors.top: informationsContainer.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        title: qsTr("Biography")
        visible: bio.text != ""
        content: Item {
            width: parent.width
            height: bio.height
            Label {
                id: bio
                width: parent.width
                wrapMode: Text.WordWrap
                text: userInfoHelper.bio
            }
        }
    }

    Container {
        id: quotesContainer
        anchors.top: bioContainer.bottom; anchors.topMargin: Ui.MARGIN_DEFAULT
        title: qsTr("Quotes")
        visible: quotes.text != ""
        content: Item {
            width: parent.width
            height: quotes.height
            Label {
                id: quotes
                width: parent.width
                wrapMode: Text.WordWrap
                text: userInfoHelper.quotes
            }
        }
    }
}
