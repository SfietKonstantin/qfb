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

#ifndef QFB_FRIENDBASE_H
#define QFB_FRIENDBASE_H

/**
 * @file friendbase.h
 * @brief Definition of QFB::FriendBase
 */

#include "base_global.h"
#include "object.h"

namespace QFB
{

class FriendBasePrivate;

/**
 * @brief Base entries for a friend
 *
 * This class represents the base entries for a friend in Facebook.
 * Extending QFB::Object, it contains the name of a friend, that
 * can be accessed through the name() property.
 */
class QFBBASE_EXPORT FriendBase : public Object
{
    Q_OBJECT
    /**
     * @short name
     */
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit FriendBase(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param id id.
     * @param name name.
     * @param parent parent object.
     */
    explicit FriendBase(const QString &id, const QString &name, QObject *parent = 0);
    /**
     * @brief Name
     * @return name.
     */
    QString name() const;
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit FriendBase(FriendBasePrivate &dd, QObject *parent = 0);
private:
    Q_DECLARE_PRIVATE(FriendBase)
};

}

#endif // QFB_FRIENDBASE_H
