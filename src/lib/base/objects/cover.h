/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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

#include "objectbase.h"
// >>>>> includes
#include <QtCore/QUrl>
// <<<<< includes

namespace QFB {
class CoverPrivate;
/**
 * @short A cover
 *
 * This class represents a cover in Facebook.
 * Extending QFB::ObjectBase, it contains a lot of properties
 * that can be accessed through
 * - source()
 * - offsetY()
 *
 * Some of these fields might not be set, because of
 * users hiding them in their settings, or because of
 * missing permissions.
 *
 * You can choose the fields you want using the "fields"
 * query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 *
 * These parameters should be added to the query that is used
 * to get a cover.
 */
class QFBBASE_EXPORT Cover: public ObjectBase
{
    Q_OBJECT
    /**
     * @short Source of the cover
     */
    Q_PROPERTY(QUrl source READ source CONSTANT)
    /**
     * @short Vertical offset
     */
    Q_PROPERTY(double offsetY READ offsetY CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
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
     * @brief Offset y
     * @return offset y.
     */
    double offsetY() const;
private:
    Q_DECLARE_PRIVATE(Cover)
};

}

Q_DECLARE_METATYPE(QFB::Cover *)


#endif // QFB_COVER_H
