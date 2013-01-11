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
 * @file poststatusloader.cpp
 * @brief Implementation of QFB::PostStatusLoader
 */

#include "poststatusloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "processors/poststatusprocessor.h"

#include "objects/object.h"
namespace QFB
{

class PostStatusLoaderPrivate: public AbstractLoaderPrivate
{
public:
    PostStatusLoaderPrivate(PostStatusLoader *q);
    Object *reply;
    QString message;
};

PostStatusLoaderPrivate::PostStatusLoaderPrivate(PostStatusLoader *q):
    AbstractLoaderPrivate(q)
{
    reply = 0;
}

////// End of private class //////

PostStatusLoader::PostStatusLoader(QObject *parent):
    AbstractGraphPostLoader(*(new PostStatusLoaderPrivate(this)), parent)
{
}

Object * PostStatusLoader::reply() const
{
    Q_D(const PostStatusLoader);
    return d->reply;
}

QString PostStatusLoader::message() const
{
    Q_D(const PostStatusLoader);
    return d->message;
}

void PostStatusLoader::setMessage(const QString &message)
{
    Q_D(PostStatusLoader);
    if(d->message != message) {
        d->message = message;
        emit messageChanged();
    }
}

QVariantMap PostStatusLoader::data() const
{
    Q_D(const PostStatusLoader);
    QVariantMap returnedData;
    returnedData.insert("message", d->message);
    return returnedData;
}

Request PostStatusLoader::createRequest(const QString &graph, const QVariantMap &data)
{
    if (queryManager()) {
        return queryManager()->queryPostStatus(graph, data);
    }
    return Request();
}

void PostStatusLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(PostStatusLoader);
    PostStatusProcessor *postStatusProcessor = qobject_cast<PostStatusProcessor *>(processor);
    if (d->reply) {
        d->reply->deleteLater();
    }

    d->reply = postStatusProcessor->reply();
    d->reply->setParent(this);
    emit replyChanged();
}

}
