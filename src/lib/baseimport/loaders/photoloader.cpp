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
 * @file photoloader.cpp
 * @brief Implementation of QFB::PhotoLoader
 */

#include "photoloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "processors/objectprocessor.h"

#include "objects/photo.h"

namespace QFB
{

class PhotoLoaderPrivate: public AbstractLoaderPrivate
{
public:
    PhotoLoaderPrivate(PhotoLoader *q);
    Photo *photo;
};

PhotoLoaderPrivate::PhotoLoaderPrivate(PhotoLoader *q):
    AbstractLoaderPrivate(q)
{
    photo = 0;
}

////// End of private class //////

PhotoLoader::PhotoLoader(QObject *parent):
    AbstractGraphLoader(*(new PhotoLoaderPrivate(this)), parent)
{
}

Photo * PhotoLoader::photo() const
{
    Q_D(const PhotoLoader);
    return d->photo;
}

Query PhotoLoader::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObject(Object::PhotoType, graph, arguments);
    }
    return Query();
}

void PhotoLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(PhotoLoader);
    ObjectProcessor *objectProcessor = qobject_cast<ObjectProcessor *>(processor);
    if (d->photo) {
        d->photo->deleteLater();
    }

    d->photo = qobject_cast<Photo*>(objectProcessor->object());
    d->photo->setParent(this);
    emit photoChanged();
}

}
