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

#ifndef QFB_PHOTOINFORMATIONS_H
#define QFB_PHOTOINFORMATIONS_H

/**
 * @file photoinformations.h
 * @brief Definition of QFB::PhotoInformations
 */

#include "objectbase.h"
// >>>>> includes
#include <QtCore/QUrl>
// <<<<< includes

namespace QFB {
class PhotoInformationsPrivate;
/**
 * @short A photoinformations
 *
 * This class represents a photoinformations in Facebook.
 * Extending QFB::ObjectBase, it contains a lot of properties
 * that can be accessed through
 * - width()
 * - height()
 * - source()
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
 * to get a photoinformations.
 */
class QFBBASE_EXPORT PhotoInformations: public ObjectBase
{
    Q_OBJECT
    /**
     * @short Width of the photo
     */
    Q_PROPERTY(int width READ width CONSTANT)
    /**
     * @short Height of the photo
     */
    Q_PROPERTY(int height READ height CONSTANT)
    /**
     * @short Source of the photo
     */
    Q_PROPERTY(QUrl source READ source CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit PhotoInformations(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit PhotoInformations(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Width
     * @return width.
     */
    int width() const;
    /**
     * @brief Height
     * @return height.
     */
    int height() const;
    /**
     * @brief Source
     * @return source.
     */
    QUrl source() const;
private:
    Q_DECLARE_PRIVATE(PhotoInformations)
};

}

Q_DECLARE_METATYPE(QFB::PhotoInformations *)


#endif // QFB_PHOTOINFORMATIONS_H
