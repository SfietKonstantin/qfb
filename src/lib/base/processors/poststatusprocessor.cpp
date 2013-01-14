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

/**
 * @file poststatusprocessor.cpp
 * @brief Implementation of QFB::PostStatusProcessor
 */

#include "poststatusprocessor.h"
#include "private/abstractgraphprocessor_p.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QIODevice>
#include "private/helper_p.h"
#include "private/object_keys_p.h"
#include "private/jsonhelper_p.h"
#include "objects/object.h"

namespace QFB
{

/**
 * @internal
 * @brief Private class for QFB::PostStatusProcessor
 */
class PostStatusProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     */
    explicit PostStatusProcessorPrivate();
    /**
     * @internal
     * @brief Reply
     */
    Object * reply;
};

PostStatusProcessorPrivate::PostStatusProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
    reply = 0;
}

////// End of private class //////

PostStatusProcessor::PostStatusProcessor(QObject *parent):
    AbstractGraphProcessor(*(new PostStatusProcessorPrivate), parent)
{
}

Object *PostStatusProcessor::reply() const
{
    Q_D(const PostStatusProcessor);
    return d->reply;
}

QByteArray PostStatusProcessor::processPostData(const QVariantMap &data)
{
    QByteArray finalData;
    finalData.append("message=");
    finalData.append(data.value("message").toString().toUtf8());
    return finalData;
}


bool PostStatusProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(PostStatusProcessor);

    QFB_JSON_GET_DOCUMENT(jsonDocument, dataSource);
    if (!QFB_JSON_CHECK_DOCUMENT(jsonDocument)) {
        setError("Received data is not a JSON document");
        return false;
    }
    QFB_JSON_GET_ROOT_OBJECT(rootObject, jsonDocument);
    QVariantMap propertiesMap;
    propertiesMap.insert(OBJECT_ID_KEY, rootObject.value(OBJECT_ID_KEY).toString());

    Object *reply = new Object(propertiesMap);
    reply->moveToThread(QCoreApplication::instance()->thread());
    d->reply = reply;

    return true;
}

}
