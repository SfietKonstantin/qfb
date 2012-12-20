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

#ifndef QFB_COVER_H
#define QFB_COVER_H

#include "base_global.h"
#include "object.h"

#include <QtCore/QUrl>

namespace QFB
{

class QFBBASE_EXPORT Cover: public Object
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source CONSTANT)
    Q_PROPERTY(double offsetY READ offsetY CONSTANT)
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Cover(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Cover(const PropertiesMap propertiesMap, QObject *parent = 0);
    QUrl source() const;
    double offsetY() const;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::Cover *)

#endif // QFB_COVER_H
