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

#ifndef QFB_POSTTAG_H
#define QFB_POSTTAG_H

/**
 * @file posttag.h
 * @brief Definition of QFB::PostTag
 */

#include "namedobject.h"
// >>>>> includes
// <<<<< includes

namespace QFB {
class PostTagPrivate;
/**
 * @short A posttag
 *
 * This class represents a posttag in Facebook.
 * Extending QFB::NamedObject, it contains a lot of properties
 * that can be accessed through
 * - offset()
 * - length()
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
 * to get a posttag.
 */
class QFBBASE_EXPORT PostTag: public NamedObject
{
    Q_OBJECT
    /**
     * @short Offset of the tag in the message
     */
    Q_PROPERTY(int offset READ offset CONSTANT)
    /**
     * @short Length of the object mentioned within the message field
     */
    Q_PROPERTY(int length READ length CONSTANT)
    // >>>>> custom header code
    // <<<<< custom header code
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit PostTag(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit PostTag(const QVariantMap propertiesMap, QObject *parent = 0);
    /**
     * @brief Offset
     * @return offset.
     */
    int offset() const;
    /**
     * @brief Length
     * @return length.
     */
    int length() const;
private:
    Q_DECLARE_PRIVATE(PostTag)
};

}

Q_DECLARE_METATYPE(QFB::PostTag *)


#endif // QFB_POSTTAG_H
