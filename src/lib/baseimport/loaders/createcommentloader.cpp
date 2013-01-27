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
 * @file createcommentloader.cpp
 * @brief Implementation of QFB::CreateCommentLoader
 */

#include "createcommentloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "processors/simplecreateobjectprocessor.h"

#include "objects/object.h"

namespace QFB
{

class CreateCommentLoaderPrivate: public AbstractLoaderPrivate
{
public:
    CreateCommentLoaderPrivate(CreateCommentLoader *q);
    Object *object;
    QString comment;
};

CreateCommentLoaderPrivate::CreateCommentLoaderPrivate(CreateCommentLoader *q):
    AbstractLoaderPrivate(q)
{
    object = 0;
}

////// End of private class //////

CreateCommentLoader::CreateCommentLoader(QObject *parent):
    AbstractGraphLoader(*(new CreateCommentLoaderPrivate(this)), parent)
{
}

Object * CreateCommentLoader::object() const
{
    Q_D(const CreateCommentLoader);
    return d->object;
}

QString CreateCommentLoader::comment() const
{
    Q_D(const CreateCommentLoader);
    return d->comment;
}

void CreateCommentLoader::setComment(const QString &comment)
{
    Q_D(CreateCommentLoader);
    if (d->comment != comment) {
        d->comment = comment;
        emit commentChanged();
    }
}

Query CreateCommentLoader::createRequest(const QString &graph, const QString &arguments)
{
    Q_UNUSED(arguments)
    Q_D(CreateCommentLoader);
    if (queryManager()) {
        QVariantMap data;
        data.insert("message", d->comment);
        return queryManager()->querySimpleCreate(graph, data);
    }
    return Query();
}

void CreateCommentLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(CreateCommentLoader);
    SimpleCreateObjectProcessor *simpleCreateObjectProcessor
            = qobject_cast<SimpleCreateObjectProcessor *>(processor);
    if (d->object) {
        d->object->deleteLater();
    }

    d->object = qobject_cast<Object*>(simpleCreateObjectProcessor->object());
    d->object->setParent(this);
    emit objectChanged();
}

}
