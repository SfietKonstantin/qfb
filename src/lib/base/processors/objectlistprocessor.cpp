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

#include "objectlistprocessor.h"
#include "private/objectprocessor_p.h"
#include <QtCore/QCoreApplication>
#include "private/abstractpagingprocessor_p.h"
#include "private/helper_p.h"
#include "private/jsonhelper_p.h"
#include "private/paging_keys_p.h"
#include "objects/object.h"

namespace QFB
{

/**
 * @internal
 * @brief DATA_KEY
 *
 * Used in QFB::ObjectListProcessor.
 */
static const char *DATA_KEY = "data";

class ObjectListProcessorPrivate: public AbstractPagingProcessorPrivate
{
public:
    explicit ObjectListProcessorPrivate();
    QList<Object *> objectList;
};

ObjectListProcessorPrivate::ObjectListProcessorPrivate():
    AbstractPagingProcessorPrivate()
{
}

////// End of private class //////

ObjectListProcessor::ObjectListProcessor(QObject *parent):
    AbstractPagingProcessor(*(new ObjectListProcessorPrivate), parent)
{
}

QList<Object *> ObjectListProcessor::objectList() const
{
    Q_D(const ObjectListProcessor);
    return d->objectList;
}

bool ObjectListProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(ObjectListProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);

    if (!rootObject.contains(DATA_KEY)) {
        setError("Received data do not contains correct data.");
        return false;
    }

    JsonArray dataArray = QFB_JSON_GET_ARRAY(rootObject.value(DATA_KEY));

    foreach (JsonValue value, dataArray) {
        if (QFB_JSON_IS_OBJECT(value)) {
            JsonObject jsonObject = QFB_JSON_GET_OBJECT(value);
            Object *object = ObjectProcessorPrivate::createObject(jsonObject, request());
            if (object) {
                d->objectList.append(object);
                object->moveToThread(QCoreApplication::instance()->thread());
            }
        }
    }

    JsonObject pagingObject = QFB_JSON_GET_OBJECT(rootObject.value(PAGING_KEY));
    QUrl previousPageUrl = parseUrl(pagingObject.value(PAGING_PREVIOUS_KEY).toString());
    setPreviousPageUrl(previousPageUrl);
    QUrl nextPageUrl = parseUrl(pagingObject.value(PAGING_NEXT_KEY).toString());
    setNextPageUrl(nextPageUrl);

    return true;
}

}
