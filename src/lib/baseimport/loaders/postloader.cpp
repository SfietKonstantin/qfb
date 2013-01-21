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
 * @file postloader.cpp
 * @brief Implementation of QFB::PostLoader
 */

#include "postloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "processors/objectprocessor.h"

#include "objects/post.h"
namespace QFB
{

class PostLoaderPrivate: public AbstractLoaderPrivate
{
public:
    PostLoaderPrivate(PostLoader *q);
    Post *post;
};

PostLoaderPrivate::PostLoaderPrivate(PostLoader *q):
    AbstractLoaderPrivate(q)
{
    post = 0;
}

////// End of private class //////

PostLoader::PostLoader(QObject *parent):
    AbstractGraphLoader(*(new PostLoaderPrivate(this)), parent)
{
}

Post * PostLoader::post() const
{
    Q_D(const PostLoader);
    return d->post;
}

Query PostLoader::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObject(Object::PostType, graph, arguments);
    }
    return Query();
}

void PostLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(PostLoader);
    ObjectProcessor *objectProcessor = qobject_cast<ObjectProcessor *>(processor);
    if (d->post) {
        d->post->deleteLater();
    }

    d->post = qobject_cast<Post*>(objectProcessor->object());
    d->post->setParent(this);
    emit postChanged();
}

}
