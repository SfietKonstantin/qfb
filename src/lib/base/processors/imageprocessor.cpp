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

#include "imageprocessor.h"
#include <QtCore/QCryptographicHash>
#include <QtCore/QDir>
#include <QtGui/QImage>
#include "private/abstractprocessor_p.h"
#include "private/cachehelper_p.h"

namespace QFB
{

class ImageProcessorPrivate: public AbstractProcessorPrivate
{
public:
    explicit ImageProcessorPrivate();
    static QString imageName(const QUrl &url);
    QString imagePath;
};

ImageProcessorPrivate::ImageProcessorPrivate():
    AbstractProcessorPrivate()
{
}

QString ImageProcessorPrivate::imageName(const QUrl &url)
{
    QByteArray asciiUrl = url.toString().toLocal8Bit();
    QByteArray encodedUrl = QCryptographicHash::hash(asciiUrl, QCryptographicHash::Md5);
    return QString("img_%1.jpg").arg(QString(encodedUrl.toHex()));
}

////// End of private class //////

ImageProcessor::ImageProcessor(QObject *parent):
    AbstractProcessor(*(new ImageProcessorPrivate), parent)
{
}

QString ImageProcessor::imagePath() const
{
    Q_D(const ImageProcessor);
    return d->imagePath;
}

bool ImageProcessor::preprocess()
{
    Q_D(ImageProcessor);
    bool needLoading = true;
    if (d->query.preprocessorData().url().isEmpty()) {
        needLoading = false;
        return false;
    }

    QDir dir (cacheFolderPath());
    QString fileName = d->imageName(d->query.preprocessorData().url());

    if (dir.exists(fileName)) {
        d->imagePath = dir.absoluteFilePath(fileName);
        needLoading = false;
    }
    setNeedLoading(needLoading);
    return true;
}

bool ImageProcessor::processDataSource(QIODevice *dataSource)
{
    Q_D(ImageProcessor);
    // Find the path to the cache
    QString path = cacheFolderPath();
    QDir::root().mkpath(path);
    QDir dir = QDir(path);
    QString fileName = d->imageName(d->query.preprocessorData().url());

    QByteArray data = dataSource->readAll();
    QImage image;
    bool ok = false;
    if (image.loadFromData(data, "JPG")) {
        ok = true;
    }
    if (!ok) {
        if (image.loadFromData(data, "PNG")) {
            ok = true;
        }
    }
    if (!ok) {
        if (image.loadFromData(data, "GIF")) {
            ok = true;
        }
    }

    if (image.isNull()) {
        return false;
    }

    d->imagePath = dir.absoluteFilePath(fileName);
    image.save(d->imagePath, "JPG");


    return true;
}

}
