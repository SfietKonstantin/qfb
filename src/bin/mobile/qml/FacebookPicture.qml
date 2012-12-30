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
import org.SfietKonstantin.qfb 4.0
import "UiConstants.js" as Ui

Image {
    id: picture
    property QtObject queryManager
    property string facebookId
    onFacebookIdChanged: pictureLoader.request(facebookId + "/picture")
    width: Ui.ICON_SIZE_DEFAULT
    height: Ui.ICON_SIZE_DEFAULT
    smooth: true
    source: pictureLoader.picturePath
    asynchronous: true
    opacity: 0
    states: State {
        name: "visible"; when: picture.status == Image.Ready
        PropertyChanges {
            target: picture
            opacity: 1
        }
    }
    Behavior on opacity {
        NumberAnimation {duration: Ui.ANIMATION_DURATION_FAST}
    }

    QFBPictureLoader {
        id: pictureLoader
        queryManager: picture.queryManager
        Component.onCompleted: request(picture.facebookId + "/picture")
    }
}
