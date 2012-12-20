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

#ifndef QFB_STATUS_H
#define QFB_STATUS_H

#include "object.h"

#include <QtCore/QDateTime>

namespace QFB
{

class UserBase;
/// @todo find an usage
/// @todo might be replaced by post
class Status: public Object
{
    Q_OBJECT
    Q_PROPERTY(QFB::UserBase * from READ from CONSTANT)
    Q_PROPERTY(QString message READ message CONSTANT)
    /// @todo place
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Status(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Status(const PropertiesMap propertiesMap, QObject *parent = 0);
    UserBase * from() const;
    QString message() const;
    QDateTime updatedTime() const;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::Status *)

#endif // QFB_STATUS_H
