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

#include "pictureloader.h"
#include <QtCore/QDebug>
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "private/picture_p.h"
#include "processors/pictureprocessor.h"

namespace QFB
{

class PictureLoaderPrivate: public AbstractLoaderPrivate
{
public:
    PictureLoaderPrivate(PictureLoader *q);
    static QString pictureString(PictureLoader::Type type);
    PictureLoader::Type type;
    QString picturePath;
};

PictureLoaderPrivate::PictureLoaderPrivate(PictureLoader *q):
    AbstractLoaderPrivate(q)
{
    type = PictureLoader::Invalid;
}

QString PictureLoaderPrivate::pictureString(PictureLoader::Type type)
{
    switch (type) {
    case PictureLoader::Square:
        return PICTURE_TYPE_SQUARE;
        break;
    case PictureLoader::Small:
        return PICTURE_TYPE_SMALL;
        break;
    case PictureLoader::Normal:
        return PICTURE_TYPE_NORMAL;
        break;
    case PictureLoader::Large:
        return PICTURE_TYPE_LARGE;
        break;
    case PictureLoader::Thumbnail:
        return PICTURE_TYPE_THUMBNAIL;
        break;
    case PictureLoader::Album:
        return PICTURE_TYPE_ALBUM;
        break;
    default:
        return QString();
        break;
    }
}

////// End of private class //////

PictureLoader::PictureLoader(QObject *parent) :
    AbstractGraphLoader(*(new PictureLoaderPrivate(this)), parent)
{
}

PictureLoader::Type PictureLoader::type() const
{
    Q_D(const PictureLoader);
    return d->type;
}

QString PictureLoader::picturePath() const
{
    Q_D(const PictureLoader);
    return d->picturePath;
}

void PictureLoader::setType(Type type)
{
    Q_D(PictureLoader);
    if (d->type != type) {
        d->type = type;
        emit typeChanged();
    }
}


Query PictureLoader::createRequest(const QString &graph, const QString &arguments)
{
    Q_D(PictureLoader);
    if (d->type == Invalid) {
        qWarning() << "Invalid image type cannot be loaded";
        return Query();
    }

    if (queryManager()) {
        QString finalArguments = arguments;
        QString newArguments = QString("%1=%2").arg(PICTURE_TYPE_KEY, d->pictureString(d->type));
        if (!arguments.isEmpty()) {
            finalArguments.append(",");
        }
        finalArguments.append(newArguments);

        return queryManager()->queryPicture(graph, finalArguments);
    }
    return Query();
}

void PictureLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(PictureLoader);
    PictureProcessor *pictureProcessor = qobject_cast<PictureProcessor *>(processor);
    QString picturePath = pictureProcessor->picturePath();
    if (d->picturePath != picturePath) {
        d->picturePath = picturePath;
        emit picturePathChanged();
    }
}

}
