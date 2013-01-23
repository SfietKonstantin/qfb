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

#include "me.h"

Me::Me(QObject *parent) :
    QObject(parent)
{
}

QString Me::facebookId() const
{
    return m_facebookId;
}

QString Me::name() const
{
    return m_name;
}

QUrl Me::coverUrl() const
{
    return m_coverUrl;
}

void Me::setFacebookId(const QString &facebookId)
{
    if (m_facebookId != facebookId) {
        m_facebookId = facebookId;
        emit facebookIdChanged();
    }
}

void Me::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

void Me::setCoverUrl(const QUrl &coverUrl)
{
    if (m_coverUrl != coverUrl) {
        m_coverUrl = coverUrl;
        emit coverUrlChanged();
    }
}
