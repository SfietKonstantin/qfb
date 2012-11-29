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
#include "querymanager.h"
#include "picturereply.h"
#include "picture_p.h"

#include <QtCore/QDebug>

namespace QFB
{

class PictureLoaderPrivate
{
public:
    PictureLoaderPrivate(PictureLoader *q);
    void slotFinished();
    void slotFailed();
    static QString pictureString(PictureLoader::Type type);
    QueryManager *queryManager;
    PictureLoader::Type type;
    QString picturePath;
    PictureReply *reply;
private:
    PictureLoader * const q_ptr;
    Q_DECLARE_PUBLIC(PictureLoader)
};

PictureLoaderPrivate::PictureLoaderPrivate(PictureLoader *q):
    q_ptr(q)
{
    queryManager = 0;
    reply = 0;
    type = PictureLoader::Square;
}

void PictureLoaderPrivate::slotFinished()
{
    Q_Q(PictureLoader);
    if (picturePath != reply->picturePath()) {
        picturePath = reply->picturePath();
        emit q->picturePathChanged();
    }

    reply->deleteLater();
    reply = 0;
}

void PictureLoaderPrivate::slotFailed()
{
    qDebug() << reply->error();
    reply->deleteLater();
    reply = 0;
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
    QObject(parent), d_ptr(new PictureLoaderPrivate(this))
{
}

PictureLoader::~PictureLoader()
{
}

QueryManager * PictureLoader::queryManager() const
{
    Q_D(const PictureLoader);
    return d->queryManager;
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

void PictureLoader::setQueryManager(QueryManager *queryManager)
{
    Q_D(PictureLoader);
    if (d->queryManager != queryManager) {
        d->queryManager = queryManager;
        emit queryManagerChanged();

    }
}


void PictureLoader::setType(Type type)
{
    Q_D(PictureLoader);
    if (d->type != type) {
        d->type = type;
        emit typeChanged();
    }
}

void PictureLoader::request(const QString &graph)
{
    Q_D(PictureLoader);

    if (!d->queryManager) {
        return;
    }

    if (d->reply) {
        return;
    }

    QString arguments = QString("%1=%2").arg(PICTURE_TYPE_KEY, d->pictureString(d->type));

    d->reply = d->queryManager->queryPicture(graph, arguments);
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->reply, SIGNAL(failed()), this, SLOT(slotFailed()));
}

}

#include "moc_pictureloader.cpp"
