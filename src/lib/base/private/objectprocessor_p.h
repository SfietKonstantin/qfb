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

#ifndef QFB_OBJECTPROCESSOR_P_H
#define QFB_OBJECTPROCESSOR_P_H

#include "private/abstractgraphprocessor_p.h"
#include "query.h"
#include "objects/object.h"
#include "private/jsonhelper_p.h"

namespace QFB
{

class ObjectProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    explicit ObjectProcessorPrivate();
    static QVariantList createArray(const JsonValue &value, const QString &key);
    static QVariant createObjectPropertiesWrapper(const QString &key, const JsonObject &object);
    static QVariantMap createObjectProperties(const JsonObject &object);
    static Object * guessType(const QVariantMap &propertiesMap, QObject *parent = 0);
    static Object * createObject(const JsonObject &jsonObject, const Query &query,
                                 QObject *parent = 0);
    Object *object;
};

}

#endif // QFB_OBJECTPROCESSOR_P_H
