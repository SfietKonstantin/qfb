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

#include "imagereply.h"
#include "abstractreply_p.h"

#include <QtCore/QCryptographicHash>
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
 * @brief Private class for QFB::ImageReply
 */
class ImageReplyPrivate: public AbstractReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    ImageReplyPrivate(ImageReply *q);
    /**
     * @internal
     * @brief Path to the cache folder
     * @return path to the cache folder.
     */
    static QString cacheFolderPath();
    /**
     * @internal
     * @brief Image name
     * @param url image url.
     * @return an image name based on the given url.
     */
    static QString imageName(const QUrl &url);
    /**
     * @internal
     * @brief Path to the image
     */
    QString imagePath;
};

ImageReplyPrivate::ImageReplyPrivate(ImageReply *q):
    AbstractReplyPrivate(q)
{
}

QString ImageReplyPrivate::cacheFolderPath()
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    return QDesktopServices::storageLocation(QDesktopServices::CacheLocation);
#else
    return QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
#endif
}

QString ImageReplyPrivate::imageName(const QUrl &url)
{
    QByteArray asciiUrl = url.toString().toAscii();
    QByteArray encodedUrl = QCryptographicHash::hash(asciiUrl, QCryptographicHash::Md5);
    return QString("img_%1.jpg").arg(QString(encodedUrl.toHex()));
}

////// End of private class //////

ImageReply::ImageReply(QObject *parent):
    AbstractReply(*(new ImageReplyPrivate(this)), parent)
{
}

ImageReply::ImageReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractReply(*(new ImageReplyPrivate(this)), parent)
{
    Q_D(ImageReply);
    d->networkAccessManager = networkAccessManager;
}

QString ImageReply::imagePath() const
{
    Q_D(const ImageReply);
    return d->imagePath;
}

void ImageReply::request(const QUrl &url)
{
    get(url);
}

bool ImageReply::preprocesssRequest()
{
    Q_D(ImageReply);

    if (url().isEmpty()) {
        return true;
    }

    QDir dir (d->cacheFolderPath());
    QString fileName = d->imageName(url());

    if (dir.exists(fileName)) {
        d->imagePath = dir.absoluteFilePath(fileName);
        return true;
    }
    return false;
}

bool ImageReply::processData(QIODevice *dataSource)
{
    Q_D(ImageReply);

    // Find the path to the cache
    QString path = d->cacheFolderPath();
    QDir::root().mkpath(path);
    QDir dir (path);
    QString fileName = d->imageName(url());

    QImage image;
    image.load(dataSource, "JPG");
    if (image.isNull()) {
        return false;
    }

    d->imagePath = dir.absoluteFilePath(fileName);
    image.save(d->imagePath);

    return true;
}

}
