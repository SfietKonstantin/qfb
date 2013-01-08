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

#include "base_global.h"
#include <QtCore/QMetaType>
#include <QtCore/QObject>
#include "qfb.h"

namespace QFB
{

class ObjectBasePrivate;
class QFBBASE_EXPORT ObjectBase : public QObject
{
    Q_OBJECT
public:
    explicit ObjectBase(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties map.
     * @param parent parent object.
     */
    explicit ObjectBase(const PropertiesMap &propertiesMap, QObject *parent = 0);
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
