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

#ifndef ME_H
#define ME_H

#include <QtCore/QObject>
#include <QtCore/QUrl>

class Me : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString facebookId READ facebookId WRITE setFacebookId NOTIFY facebookIdChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QUrl coverUrl READ coverUrl WRITE setCoverUrl NOTIFY coverUrlChanged)
public:
    explicit Me(QObject *parent = 0);
    QString facebookId() const;
    QString name() const;
    QUrl coverUrl() const;
public slots:
    void setFacebookId(const QString &facebookId);
    void setName(const QString &name);
    void setCoverUrl(const QUrl &coverUrl);
signals:
    void facebookIdChanged();
    void nameChanged();
    void coverUrlChanged();
private:
    QString m_facebookId;
    QString m_name;
    QUrl m_coverUrl;
};

#endif // ME_H
