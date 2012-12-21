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
#include "loaderbase_p.h"

#include "querymanager.h"
#include "picturereply.h"
#include "picture_p.h"

namespace QFB
{

class PictureLoaderPrivate: public LoaderBasePrivate
{
public:
    PictureLoaderPrivate(PictureLoader *q);
    bool checkReply(const AbstractReply *reply);
    void processReply(const AbstractReply *reply);
    static QString pictureString(PictureLoader::Type type);
    PictureLoader::Type type;
    QString picturePath;
private:
    Q_DECLARE_PUBLIC(PictureLoader)
};

PictureLoaderPrivate::PictureLoaderPrivate(PictureLoader *q):
    LoaderBasePrivate(q)
{
    type = PictureLoader::Square;
}

bool PictureLoaderPrivate::checkReply(const AbstractReply *reply)
{
        return qobject_cast<const PictureReply *>(reply);
}

void PictureLoaderPrivate::processReply(const AbstractReply *reply)
{
    Q_Q(PictureLoader);
    const PictureReply *pictureReply = qobject_cast<const PictureReply *>(reply);
    if (picturePath != pictureReply->picturePath()) {
        picturePath = pictureReply->picturePath();
        emit q->picturePathChanged();
    }
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

AbstractGraphReply * PictureLoader::createReply(const QString &graph, const QString &arguments)
{
    Q_D(PictureLoader);
    QString finalArguments = arguments;
    QString newArguments = QString("%1=%2").arg(PICTURE_TYPE_KEY, d->pictureString(d->type));
    if (!arguments.isEmpty()) {
        finalArguments.append(",");
    }
    finalArguments.append(newArguments);

    return queryManager()->queryPicture(graph, finalArguments);
}

}
