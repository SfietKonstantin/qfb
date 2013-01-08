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

#include "pictureprocessor.h"
#include "abstractgraphprocessor_p.h"
#include <QtCore/QDir>
#include <QtGui/QImage>
#include "cachehelper_p.h"
#include "picture_p.h"

namespace QFB
{

class PictureProcessorPrivate: public AbstractGraphProcessorPrivate
{
public:
    explicit PictureProcessorPrivate();
    QString pictureName(const QString &graph, const QList<ArgumentPair> &arguments);
    QString picturePath;
};

PictureProcessorPrivate::PictureProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
}

QString PictureProcessorPrivate::pictureName(const QString &graph,
                                             const QList<ArgumentPair> &arguments)
{
    QString suffix = arguments.first().second;
    QString newGraph = graph;
    newGraph.replace("/", "-");
    return QString("pic_%1_%2.jpg").arg(newGraph, suffix);
}


////// End of private class //////

PictureProcessor::PictureProcessor(QObject *parent):
    AbstractGraphProcessor(*(new PictureProcessorPrivate), parent)
{
}

QString PictureProcessor::picturePath() const
{
    Q_D(const PictureProcessor);
    return d->picturePath;
}

bool PictureProcessor::processGraphAndArguments(const QString &graph,
                                                const QList<ArgumentPair> &arguments)
{
    Q_D(PictureProcessor);
    // Get the true arguments
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
    setPreprocessedData(graph, trueArguments);

    // Check if the picture is already cached
    QDir dir (cacheFolderPath());
    QString fileName = d->pictureName(graph, trueArguments);

    if (dir.exists(fileName)) {
        d->picturePath = dir.absoluteFilePath(fileName);
        setNeedLoading(false);
    }
    return true;
}

bool PictureProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(PictureProcessor);

    // Find the path to the cache
    QString path = cacheFolderPath();
    QDir::root().mkpath(path);
    QDir dir = QDir(path);
    QString fileName = d->pictureName(request().graph(), request().arguments());

    QImage image;
    bool ok = false;
    if (image.load(dataSource, "JPG")) {
        ok = true;
    }
    if (!ok) {
        if (image.load(dataSource, "GIF")) {
            ok = true;
        }
    }
    if (!ok) {
        if (image.load(dataSource, "PNG")) {
            ok = true;
        }
    }

    if (image.isNull()) {
        return false;
    }

    d->picturePath = dir.absoluteFilePath(fileName);
    image.save(d->picturePath, "JPG");

    return true;
}

}
