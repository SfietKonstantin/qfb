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

#ifndef QFB_LANGUAGE_H
#define QFB_LANGUAGE_H

/**
 * @file language.h
 * @brief Definition of QFB::Language
 */

#include "object.h"

namespace QFB
{

/**
 * @brief A language used by a user
 *
 * This class represents a language used by a user.
 * Extending QFB::Object, it contains the name of that
 * language, that can be accessed through the name()
 * property.
 */
class QFBBASE_EXPORT Language: public Object
{
    Q_OBJECT
    /**
     * @short Name
     */
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Language(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Language(const PropertiesMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Name
     * @return name.
     */
    QString name() const;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::Language *)

#endif // QFB_LANGUAGE_H
