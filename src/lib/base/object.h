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
#include <QtCore/QObject>

namespace QFB
{

class ObjectPrivate;

/**
 * @brief An object in Facebook
 *
 * This class represents any entity in Facebook, as
 * a QObject based object. All Facebook entities
 * provides an id, that can be accessed though the id()
 * property.
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
     * @param id id.
     * @param parent parent object.
     */
    explicit Object(const QString &id, QObject *parent = 0);
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

#endif // QFB_OBJECT_H
