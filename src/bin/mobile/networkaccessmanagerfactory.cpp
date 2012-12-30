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

#include "networkaccessmanagerfactory.h"
#include "networkaccessmanager.h"

static const char *N9_USER_AGENT = "    Mozilla/5.0 (MeeGo; NokiaN9) AppleWebKit/534.13 \
(KHTML, like Gecko) NokiaBrowser/8.5.0 Mobile Safari/534.13 ";

QNetworkAccessManager * NetworkAccessManagerFactory::create(QObject *parent)
{
    NetworkAccessManager *networkAccessManager = new NetworkAccessManager(parent);
    networkAccessManager->setUserAgent(N9_USER_AGENT);
    return networkAccessManager;
}
