/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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

#include "cookiejar.h"
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtGui/QDesktopServices>

namespace QFB
{

class CookieJarPrivate
{
public:
    void load();
    void save();
    QList<QNetworkCookie> cookies;
};

void CookieJarPrivate::load()
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dir (path);
    QFile file (dir.filePath("cookies"));
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    while (!file.atEnd()) {
        QByteArray data = file.readLine();
        QList<QNetworkCookie> parsedCookies = QNetworkCookie::parseCookies(data);
        cookies.append(parsedCookies);
    }


    file.close();
}

void CookieJarPrivate::save()
{
    QString path = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir::root().mkpath(path);
    QDir dir (path);
    QFile file (dir.filePath("cookies"));
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    foreach (QNetworkCookie cookie, cookies) {
        file.write(cookie.toRawForm());
        file.write("\n");
    }

    file.close();

}

////// End of private class //////

CookieJar::CookieJar(QObject *parent) :
    QNetworkCookieJar(parent), d_ptr(new CookieJarPrivate)
{
    Q_D(CookieJar);
    d->load();
    setAllCookies(d->cookies);

}

CookieJar::~CookieJar()
{
}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url)
{
    Q_D(CookieJar);
    QList<QNetworkCookie> trueCookieList;
    foreach (QNetworkCookie cookie, cookieList) {
        if (!cookie.isSessionCookie()) {
            trueCookieList.append(cookie);
        }
    }

    if (!trueCookieList.isEmpty()) {
        d->cookies.append(trueCookieList);
    }
    d->save();
    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}

}
