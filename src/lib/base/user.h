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

#ifndef QFB_USER_H
#define QFB_USER_H

#include "userbase.h"
#include <QtCore/QDate>

namespace QFB
{

class QFBBASE_EXPORT User : public UserBase
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName CONSTANT)
    Q_PROPERTY(QString middleName READ middleName CONSTANT)
    Q_PROPERTY(QString lastName READ lastName CONSTANT)
    Q_PROPERTY(QString gender READ gender CONSTANT)
    Q_PROPERTY(QString locale READ locale CONSTANT)
    /// @todo languages
    Q_PROPERTY(QString link READ link CONSTANT)
    Q_PROPERTY(QString username READ username CONSTANT)
    /// @todo no third_party_id
    /// @todo no installed
    /// @todo no timezone
    /// @todo no updated_time
    /// @todo no verified
    Q_PROPERTY(QString bio READ bio CONSTANT)
    Q_PROPERTY(QDate birthday READ birthday CONSTANT)

public:
    explicit User(QObject *parent = 0);
    explicit User(const PropertiesMap propertiesMap, QObject *parent = 0);
    QString firstName() const;
    QString middleName() const;
    QString lastName() const;
    QString gender() const;
    QString locale() const;
    QString link() const;
    QString username() const;
    QString bio() const;
    QDate birthday() const;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::User *)

#endif // QFB_USER_H
