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
import QtWebKit 1.0
import com.nokia.meego 1.0
import org.SfietKonstantin.qfb 4.0
import org.SfietKonstantin.qfb.login 4.0

PageStackWindow {
    id: window
    initialPage: mainPage

    QFBQueryManager {
        id: queryManager
        onTokenChanged: {
            if (token != "") {
                mainPage.load()
            }
        }
    }

    QFBLoginManager {
        id: loginManager
        clientId: "390204064393625"
        uiType: QFBLoginManager.Mobile
        Component.onCompleted: {
            if (TOKEN_MANAGER.token == "") {
                loginSheet.open()
                login()
            } else {
                queryManager.token = TOKEN_MANAGER.token
            }
        }

        onLoginSucceeded: {
            TOKEN_MANAGER.token = token
            queryManager.token = token
            loginSheet.accept()
        }
    }

    LoginSheet {
        id: loginSheet
        loginManager: loginManager
    }

    MainPage {
        id: mainPage
        queryManager: queryManager
    }

}
