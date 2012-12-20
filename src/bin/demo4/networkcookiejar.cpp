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

#include "networkcookiejar.h"
#include <QtCore/QSettings>
#include <QtCore/QDebug>

NetworkCookieJar::NetworkCookieJar(QObject *parent):
    QNetworkCookieJar(parent)
{
    load();
}

NetworkCookieJar::~NetworkCookieJar()
{
    save();
}

void NetworkCookieJar::load()
{
    QSettings settings;
    QByteArray data = settings.value("cookies").toByteArray();
    setAllCookies(QNetworkCookie::parseCookies(data));
}

void NetworkCookieJar::save()
{
    QList<QNetworkCookie> list = allCookies();
    QByteArray data;
    foreach (QNetworkCookie cookie, list) {
        if (!cookie.isSessionCookie()) {
            data.append(cookie.toRawForm());
            data.append("\n");
        }
    }
    QSettings settings;
    settings.setValue("cookies", data);
}

