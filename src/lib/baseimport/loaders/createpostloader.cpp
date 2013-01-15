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
 * @file createpostloader.cpp
 * @brief Implementation of QFB::CreatePostLoader
 */

#include "createpostloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "processors/simplecreateobjectprocessor.h"

#include "objects/object.h"
namespace QFB
{

class CreatePostLoaderPrivate: public AbstractLoaderPrivate
{
public:
    CreatePostLoaderPrivate(CreatePostLoader *q);
    Object *reply;
    QString message;
};

CreatePostLoaderPrivate::CreatePostLoaderPrivate(CreatePostLoader *q):
    AbstractLoaderPrivate(q)
{
    reply = 0;
}

////// End of private class //////

CreatePostLoader::CreatePostLoader(QObject *parent):
    AbstractGraphPostLoader(*(new CreatePostLoaderPrivate(this)), parent)
{
}

Object * CreatePostLoader::reply() const
{
    Q_D(const CreatePostLoader);
    return d->reply;
}

QString CreatePostLoader::message() const
{
    Q_D(const CreatePostLoader);
    return d->message;
}

void CreatePostLoader::setMessage(const QString &message)
{
    Q_D(CreatePostLoader);
    if(d->message != message) {
        d->message = message;
        emit messageChanged();
    }
}

QVariantMap CreatePostLoader::data() const
{
    Q_D(const CreatePostLoader);
    QVariantMap returnedData;
    returnedData.insert("message", d->message);
    return returnedData;
}

Request CreatePostLoader::createRequest(const QString &graph, const QVariantMap &data)
{
    if (queryManager()) {
        return queryManager()->querySimpleCreate(graph, data);
    }
    return Request();
}

void CreatePostLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(CreatePostLoader);
    SimpleCreateObjectProcessor *postProcessor = qobject_cast<SimpleCreateObjectProcessor *>(processor);
    if (d->reply) {
        d->reply->deleteLater();
    }

    d->reply = postProcessor->object();
    d->reply->setParent(this);
    emit replyChanged();
}

}
