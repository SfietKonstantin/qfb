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

#ifndef QFB_OBJECT_H
#define QFB_OBJECT_H

/**
 * @file object.h
 * @brief Definition of QFB::Object
 */

#include "base_global.h"
#include "qfb.h"

#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QVariant>

namespace QFB
{

/**
 * @brief Properties map
 *
 * This typedef defines a mapping between a proprety name,
 * defined in the QFB::Property enumeration, and the
 * value of that property.
 *
 */
typedef QMap<Property, QVariant> PropertiesMap;
class ObjectPrivate;
/**
 * @brief An object in Facebook
 *
 * This class represents any entity in Facebook, as
 * a QObject based object. All Facebook entities
 * provides an id, that can be accessed though the id()
 * property.
 *
 * All Facebook entities can carry quite a lot of types
 * of data, and this class is responsible in storing them.
 * The properties of a Facebook entity is passed as a
 * mapping between a property and the corresponding value.
 */
class QFBBASE_EXPORT Object : public QObject
{
    Q_OBJECT
    /**
     * @short id
     */
    Q_PROPERTY(QString id READ id CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Object(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties map.
     * @param parent parent object.
     */
    explicit Object(const PropertiesMap &propertiesMap, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~Object();
    /**
     * @brief Id
     * @return id.
     */
    QString id() const;
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit Object(ObjectPrivate &dd, QObject *parent = 0);
    /**
     * @brief D-pointer
     */
    QScopedPointer<ObjectPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::Object *)

#endif // QFB_OBJECT_H
