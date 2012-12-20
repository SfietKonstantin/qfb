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
 * @file picturereply.cpp
 * @brief Implementation of QFB::PictureReply
 */

#include "picturereply.h"
#include "abstractgraphreply_p.h"
#include "picture_p.h"

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtGui/QImage>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QtGui/QDesktopServices>
#else
#include <QtCore/QStandardPaths>
#endif



namespace QFB
{

/**
 * @internal
 * @brief Private class for QFB::PictureReply
 */
class PictureReplyPrivate: public AbstractGraphReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    PictureReplyPrivate(PictureReply *q);
    /**
     * @internal
     * @brief Path to the cache folder
     * @return path to the cache folder.
     */
    static QString cacheFolderPath();
    /**
     * @internal
     * @brief Picture name
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     * @return a picture name based on the graph entry and the arguments.
     */
    static QString pictureName(const QString &graph, const QList<ArgumentPair> &arguments);
    /**
     * @internal
     * @brief Path to the picture
     */
    QString picturePath;
};

PictureReplyPrivate::PictureReplyPrivate(PictureReply *q):
    AbstractGraphReplyPrivate(q)
{
}

QString PictureReplyPrivate::cacheFolderPath()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    return QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#endif
}

QString PictureReplyPrivate::pictureName(const QString &graph, const QList<ArgumentPair> &arguments)
{
    QString suffix = arguments.first().second;
    QString newGraph = graph;
    newGraph.replace("/", "-");
    return QString("pic_%1_%2.jpg").arg(newGraph, suffix);
}

////// End of private class //////

PictureReply::PictureReply(QObject *parent):
    AbstractGraphReply(*(new PictureReplyPrivate(this)), parent)
{
}

PictureReply::PictureReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractGraphReply(*(new PictureReplyPrivate(this)), parent)
{
    Q_D(PictureReply);
    d->networkAccessManager = networkAccessManager;
}

QString PictureReply::picturePath() const
{
    Q_D(const PictureReply);
    return d->picturePath;
}

QList<ArgumentPair> PictureReply::processArguments(const QList<ArgumentPair> &arguments)
{
    // Extract the type
    QString type;

    foreach(ArgumentPair argument, arguments) {
        if (argument.first == PICTURE_TYPE_KEY) {
            if (argument.second == PICTURE_TYPE_SQUARE
                || argument.second == PICTURE_TYPE_SMALL
                || argument.second == PICTURE_TYPE_NORMAL
                || argument.second == PICTURE_TYPE_LARGE) {
                type = argument.second;
            }
        }
    }

    QList<ArgumentPair> trueArguments;
    if (type.isEmpty()) {
        trueArguments.append(ArgumentPair(PICTURE_TYPE_KEY, PICTURE_TYPE_SQUARE));
    } else {
        trueArguments.append(ArgumentPair(PICTURE_TYPE_KEY, type));
    }
    return trueArguments;
}

bool PictureReply::preprocesssRequest()
{
    Q_D(PictureReply);

    QDir dir (d->cacheFolderPath());
    QString fileName = d->pictureName(graph(), arguments());

    if (dir.exists(fileName)) {
        d->picturePath = dir.absoluteFilePath(fileName);
        return true;
    }
    return false;
}

bool PictureReply::processData(QIODevice *dataSource)
{
    Q_D(PictureReply);

    // Find the path to the cache
    QString path = d->cacheFolderPath();
    QDir::root().mkpath(path);
    QDir dir (path);
    QString fileName = d->pictureName(graph(), arguments());

    QImage image;
    if (!image.load(dataSource, "JPG")) {
        image.load(dataSource, "GIF");
    }
    if (image.isNull()) {
        return false;
    }

    d->picturePath = dir.absoluteFilePath(fileName);
    image.save(d->picturePath, "JPG");

    return true;
}

}
