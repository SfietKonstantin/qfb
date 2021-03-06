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

#ifndef QFB_PROCESSORHELPER_P_H
#define QFB_PROCESSORHELPER_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.


#include "jsonhelper_p.h"
#include "namedobject_keys_p.h"
#include "object_keys_p.h"
#include "objects/namedobject.h"

namespace QFB
{

inline QVariant createNamedObject(const JsonObject &jsonObject)
{
    PropertiesMap namedObjectPropertiesMap;
    namedObjectPropertiesMap.insert(OBJECT_ID_KEY, jsonObject.value(OBJECT_ID_KEY).toString());
    namedObjectPropertiesMap.insert(NAMEDOBJECT_NAME_KEY,
                                    jsonObject.value(NAMEDOBJECT_NAME_KEY).toString());
    return QVariant::fromValue(new NamedObject(namedObjectPropertiesMap));
}

}

#endif // QFB_PROCESSORHELPER_P_H
