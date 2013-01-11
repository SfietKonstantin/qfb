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

#ifndef QFB_OBJECTBASE_H
#define QFB_OBJECTBASE_H

/**
 * @file objectbase.h
 * @brief Definition of QFB::ObjectBase
 */

#include "base_global.h"
#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include "qfb.h"

namespace QFB
{

class ObjectBasePrivate;
/**
 * @brief Base class for Facebook objects
 *
 * This class represent a basic Facebook entity
 * that do not even have an id.
 *
 * Facebook entities can carry quite a lot of types
 * of data, and this class is responsible in storing them.
 * The properties of a Facebook entity is passed as a
 * mapping between a property key, that is the string used
 * in the facebook API and the corresponding value.
 *
 * @see Object
 */
class QFBBASE_EXPORT ObjectBase : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit ObjectBase(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties map.
     * @param parent parent object.
     */
    explicit ObjectBase(const PropertiesMap &propertiesMap, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~ObjectBase();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit ObjectBase(ObjectBasePrivate &dd, QObject *parent = 0);
    /**
     * @brief D-pointer
     */
    QScopedPointer<ObjectBasePrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

#endif // QFB_OBJECTBASE_H
