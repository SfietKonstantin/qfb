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

#ifndef QFB_JSONHELPER_P_H
#define QFB_JSONHELPER_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file jsonhelper_p.h
 * @short JSON helper macros
 */

/**
 * @internal
 * @typedef JsonObject
 * @short A JSON object
 */
/**
 * @internal
 * @typedef JsonValue
 * @short A JSON value
 */
/**
 * @internal
 * @typedef JsonArray
 * @short A JSON array
 */
/**
 * @internal
 * @def QFB_JSON_IS_ARRAY
 * @short Check if a JSON value is an array
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_IS_BOOL
 * @short Check if a JSON value is a boolean
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_IS_DOUBLE
 * @short Check if a JSON value is a double
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_IS_OBJECT
 * @short Check if a JSON value is an object
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_IS_STRING
 * @short Check if a JSON value is a string
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_GET_ARRAY
 * @short Get an array from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_GET_BOOL
 * @short Get a boolean from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_GET_DOUBLE
 * @short Get a double from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_GET_OBJECT
 * @short Get an object from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_GET_STRING
 * @short Get a string from a JSON value
 * @param jsonValue JSON value
 */
/**
 * @internal
 * @def QFB_JSON_GET_DOCUMENT
 * @short Extract a JSON document from a data source
 * @param jsonDocument name of the JSON document variable.
 * @param dataSource data source, as a QIODevice.
 */
/**
 * @internal
 * @def QFB_JSON_CHECK_DOCUMENT
 * @short Check if a JSON document is valid
 * @param jsonDocument JSON document to check.
 */
/**
 * @internal
 * @def QFB_JSON_GET_ROOT_OBJECT
 * @short Get the root object from the JSON document
 * @param jsonDocument JSON document.
 * @param rootObject name of the root object.
 */

#include <QtCore/QtGlobal>

// Includes
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtCore/QVariantMap>
#include <QtCore/QVariantList>
#include "parser.h"
#else
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>
#endif


#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
// Typedefs
typedef QVariantMap JsonObject;
typedef QVariant JsonValue;
typedef QVariantList JsonArray;
// Checks
#define QFB_JSON_IS_ARRAY(jsonValue) jsonValue.canConvert(QVariant::List)
#define QFB_JSON_IS_BOOL(jsonValue) jsonValue.canConvert(QVariant::Bool)
#define QFB_JSON_IS_DOUBLE(jsonValue) jsonValue.canConvert(QVariant::Double)
#define QFB_JSON_IS_OBJECT(jsonValue) jsonValue.canConvert(QVariant::Map)
#define QFB_JSON_IS_STRING(jsonValue) jsonValue.canConvert(QVariant::String)
// Getters
#define QFB_JSON_GET_ARRAY(jsonValue) jsonValue.toList()
#define QFB_JSON_GET_BOOL(jsonValue) jsonValue.toBool()
#define QFB_JSON_GET_DOUBLE(jsonValue) jsonValue.toDouble()
#define QFB_JSON_GET_OBJECT(jsonValue) jsonValue.toMap()
#define QFB_JSON_GET_STRING(jsonValue) jsonValue.toString()
// Helpers
#define QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource) QJson::Parser parser; \
    QVariant jsonDocument = parser.parse(dataSource)
#define QFB_JSON_CHECK_DOCUMENT(jsonDocument) jsonDocument.isValid()
#define QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument) \
    JsonObject rootObject = jsonDocument.toMap()
#else
// Typedefs
typedef QJsonObject JsonObject;
typedef QJsonValue JsonValue;
typedef QJsonArray JsonArray;
// Checks
#define QFB_JSON_IS_ARRAY(jsonValue) jsonValue.isArray()
#define QFB_JSON_IS_BOOL(jsonValue) jsonValue.isBool()
#define QFB_JSON_IS_DOUBLE(jsonValue) jsonValue.isDouble()
#define QFB_JSON_IS_OBJECT(jsonValue) jsonValue.isObject()
#define QFB_JSON_IS_STRING(jsonValue) jsonValue.isString()
// Getters
#define QFB_JSON_GET_ARRAY(jsonValue) jsonValue.toArray()
#define QFB_JSON_GET_BOOL(jsonValue) jsonValue.toBool()
#define QFB_JSON_GET_DOUBLE(jsonValue) jsonValue.toDouble()
#define QFB_JSON_GET_OBJECT(jsonValue) jsonValue.toObject()
#define QFB_JSON_GET_STRING(jsonValue) jsonValue.toString()
// Helpers
#define QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource) \
    QJsonDocument jsonDocument = QJsonDocument::fromJson(dataSource->readAll())
#define QFB_JSON_CHECK_DOCUMENT(jsonDocument) !jsonDocument.isNull()
#define QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument) \
    JsonObject rootObject = jsonDocument.object()
#endif

#endif // QFB_JSONHELPER_P_H
