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

#include <QtGui/QApplication>
#include <QtDeclarative/qdeclarative.h>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeView>

#include "userinfohelper.h"
#include "querymanager.h"
#include "loginmanager.h"
#include "tokenmanager.h"
#include "networkaccessmanagerfactory.h"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    app.setOrganizationName("SfietKonstantin");
    app.setApplicationName("qfb-mobile");

    QFB::QueryManager queryManager;
    QFB::LoginManager loginManager;
    TokenManager tokenManager;

    qmlRegisterType<UserInfoHelper>("org.SfietKonstantin.qfb.mobile", 4, 0, "QFBUserInfoHelper");

    QDeclarativeView view;
    view.engine()->addImportPath(IMPORT_PATH);
    view.engine()->setNetworkAccessManagerFactory(new NetworkAccessManagerFactory());
    view.rootContext()->setContextProperty("QUERY_MANAGER", &queryManager);
    view.rootContext()->setContextProperty("LOGIN_MANAGER", &loginManager);
    view.rootContext()->setContextProperty("TOKEN_MANAGER", &tokenManager);
    view.setSource(QUrl(MAIN_QML_FILE));
    view.showFullScreen();
    QObject::connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));

    return app.exec();
}
