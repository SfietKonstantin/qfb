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

#ifndef QFB_NAMEDOBJECT_H
#define QFB_NAMEDOBJECT_H

/**
 * @file namedobject.h
 * @brief Definition of QFB::NamedObject
 */

#include "object.h"

namespace QFB
{

/**
 * @brief Base entries for a named object
 *
 * This class represents the base entries for a named object in
 * Facebook. Extending QFB::Object, it contains the name of that
 * object, that can be accessed through the name() property.
 *
 * Often, named objects represents users, with an id and a name,
 * but they can also represent groups, pages etc.
 */
class QFBBASE_EXPORT NamedObject : public Object
{
    Q_OBJECT
    /**
     * @short The user's full name
     */
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit NamedObject(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit NamedObject(const PropertiesMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Name
     * @return name.
     */
    QString name() const;
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::NamedObject *)

#endif // QFB_NAMEDOBJECT_H
