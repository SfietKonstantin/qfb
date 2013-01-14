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

#ifndef QFB_OBJECT_CREATOR_P_H
#define QFB_OBJECT_CREATOR_P_H

#include <QtCore/QList>
#include "qfb.h"

namespace QFB
{

template <class T> inline T * createObject(const QVariantMap &propertiesMap, QObject *parent = 0)
{
    return new T(propertiesMap, parent);
}

inline QList<QString> createStringList(const QVariantList &propertiesList)
{
    QList<QString> data;
    foreach (QVariant properties, propertiesList) {
        data.append(properties.toString());
    }
    return data;
}

template <class T> inline QList<T *> createList(const QVariantList &propertiesList,
                                                QObject *parent = 0)
{
    QList<T *> data;
    foreach (QVariant properties, propertiesList) {
        data.append(new T(properties.toMap(), parent));
    }
    return data;
}

}

#endif // QFB_OBJECT_CREATOR_P_H
