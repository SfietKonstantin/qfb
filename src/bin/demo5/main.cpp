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

#include <QtGui/QGuiApplication>
#include <QtQml/qqml.h>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>

#include "loginmanager.h"
#include "bridge.h"

int main(int argc, char **argv)
{
    QGuiApplication app (argc, argv);
    app.setOrganizationName("SfietKonstantin");
    app.setApplicationName("qfb-demo");

    Bridge bridge;

    qmlRegisterType<QFB::LoginManager>("org.SfietKonstantin.qfb.login", 5, 0, "QFBLoginManager");

    QQuickView view;
    view.engine()->addImportPath(IMPORT_PATH);
    view.rootContext()->setContextProperty("BRIDGE", &bridge);
    view.setSource(QUrl(MAIN_QML_FILE));
    view.show();

    return app.exec();
}
