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

#ifndef USERINFOHELPER_H
#define USERINFOHELPER_H

#include <QtCore/QObject>
#include "user.h"

class UserInfoHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QFB::User * user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(QString formattedInformations READ formattedInformations
               NOTIFY formattedInformationsChanged)
    Q_PROPERTY(QString bio READ bio NOTIFY bioChanged)
    Q_PROPERTY(QString quotes READ quotes NOTIFY quotesChanged)
public:
    explicit UserInfoHelper(QObject *parent = 0);
    QFB::User * user() const;
    QString formattedInformations() const;
    QString bio() const;
    QString quotes() const;
public slots:
    void setUser(QFB::User *user);
signals:
    void formattedInformationsChanged();
    void userChanged();
    void bioChanged();
    void quotesChanged();
private:
    void createText();
    QFB::User *m_user;
    QString m_formattedInformations;
    QString m_bio;
    QString m_quotes;
};

#endif // USERINFOHELPER_H
