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

/**
 * @file cover.h
 * @brief Definition of QFB::Cover
 */

#include "object.h"

#include <QtCore/QUrl>

namespace QFB
{

/**
 * @brief Information about a cover
 *
 * This class represents a cover. Extending QFB::Object,
 * it contains the source of the cover, that can be accessed
 * through the source() property, and the vertical offset that
 * is used to display it, and that can be accessed through
 * offsetY().
 */
class QFBBASE_EXPORT Cover: public Object
{
    Q_OBJECT
    /**
     * @short Source
     */
    Q_PROPERTY(QUrl source READ source CONSTANT)
    /**
     * @short Vertical offset
     */
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
    explicit Cover(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Source
     * @return source.
     */
    QUrl source() const;
    /**
     * @short Vertical offset
     * @return vertical offset.
     */
    double offsetY() const;
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::Cover *)

#endif // QFB_COVER_H
