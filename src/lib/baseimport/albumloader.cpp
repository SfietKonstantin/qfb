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

#include "albumloader.h"
#include "abstractloader_p.h"
#include "querymanager.h"
#include "album.h"
#include "albumprocessor.h"

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

AlbumLoader::AlbumLoader(QObject *parent) :
    AbstractGraphLoader(*(new AlbumLoaderPrivate(this)), parent)
{
}

Album * AlbumLoader::album() const
{
    Q_D(const AlbumLoader);
    return d->album;
}

Request AlbumLoader::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryAlbum(graph, arguments);
    }
    return Request();
}

void AlbumLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(AlbumLoader);
    AlbumProcessor *albumProcessor = qobject_cast<AlbumProcessor *>(processor);
    if (d->album) {
        d->album->deleteLater();
    }

    d->album = albumProcessor->album();
    d->album->setParent(this);
    emit albumChanged();
}

}
