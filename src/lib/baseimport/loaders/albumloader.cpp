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
 * @file albumloader.cpp
 * @brief Implementation of QFB::AlbumLoader
 */

#include "albumloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "processors/objectprocessor.h"

#include "objects/album.h"

namespace QFB
{

class AlbumLoaderPrivate: public AbstractLoaderPrivate
{
public:
    AlbumLoaderPrivate(AlbumLoader *q);
    Album *album;
};

AlbumLoaderPrivate::AlbumLoaderPrivate(AlbumLoader *q):
    AbstractLoaderPrivate(q)
{
    album = 0;
}

////// End of private class //////

AlbumLoader::AlbumLoader(QObject *parent):
    AbstractGraphLoader(*(new AlbumLoaderPrivate(this)), parent)
{
}

Album * AlbumLoader::album() const
{
    Q_D(const AlbumLoader);
    return d->album;
}

Query AlbumLoader::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObject(Object::AlbumType, graph, arguments);
    }
    return Query();
}

void AlbumLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(AlbumLoader);
    ObjectProcessor *objectProcessor = qobject_cast<ObjectProcessor *>(processor);
    if (d->album) {
        d->album->deleteLater();
    }

    d->album = qobject_cast<Album*>(objectProcessor->object());
    d->album->setParent(this);
    emit albumChanged();
}

}
