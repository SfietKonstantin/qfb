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

#include "networkaccessmanager.h"
#include <QtNetwork/QNetworkRequest>

NetworkAccessManager::NetworkAccessManager(QObject *parent):
    QNetworkAccessManager(parent)
{
}

NetworkAccessManager::NetworkAccessManager(const QString &userAgent, QObject *parent):
    QNetworkAccessManager(parent)
{
    m_userAgent = userAgent;
}

void NetworkAccessManager::setUserAgent(const QString &userAgent)
{
    m_userAgent = userAgent;
}

QNetworkReply * NetworkAccessManager::createRequest(Operation op, const QNetworkRequest &request,
                                                    QIODevice *outgoingData)
{
    if (m_userAgent.isEmpty()) {
        return QNetworkAccessManager::createRequest(op, request, outgoingData);
    }

    QNetworkRequest newRequest (request);
    newRequest.setRawHeader("User-Agent", m_userAgent.toAscii());
    return QNetworkAccessManager::createRequest(op, newRequest, outgoingData);
}
