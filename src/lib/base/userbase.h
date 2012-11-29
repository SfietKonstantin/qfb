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

#ifndef QFB_USERBASE_H
#define QFB_USERBASE_H

/**
 * @file userbase.h
 * @brief Definition of QFB::UserBase
 */

#include "base_global.h"
#include "object.h"

namespace QFB
{

class UserBasePrivate;

/**
 * @brief Base entries for a friend
 *
 * This class represents the base entries for a friend in Facebook.
 * Extending QFB::Object, it contains the name of a friend, that
 * can be accessed through the name() property.
 */
class QFBBASE_EXPORT UserBase : public Object
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
    explicit UserBase(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param id id.
     * @param name name.
     * @param parent parent object.
     */
    explicit UserBase(const PropertiesMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Name
     * @return name.
     */
    QString name() const;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::UserBase *)

#endif // QFB_USERBASE_H
