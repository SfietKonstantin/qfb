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

#include "imageloader.h"
#include "abstractloader_p.h"
#include "imageprocessor.h"
#include "querymanager.h"

namespace QFB
{

class ImageLoaderPrivate: public AbstractLoaderPrivate
{
public:
    ImageLoaderPrivate(ImageLoader *q);
    QString imagePath;
};

ImageLoaderPrivate::ImageLoaderPrivate(ImageLoader *q):
    AbstractLoaderPrivate(q)
{
}

////// End of private class //////

ImageLoader::ImageLoader(QObject *parent) :
    AbstractLoader(*(new ImageLoaderPrivate(this)), parent)
{
}

QString ImageLoader::imagePath() const
{
    Q_D(const ImageLoader);
    return d->imagePath;
}

void ImageLoader::request(const QUrl &url)
{
    Request createdRequest = createRequest(url);
    if (createdRequest.isValid()) {
        handleRequest(createdRequest);
    }
}

Request ImageLoader::createRequest(const QUrl &url)
{
    if (queryManager()) {
        return queryManager()->queryImage(url);
    }
    return Request();
}

void ImageLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(ImageLoader);
    ImageProcessor *imageProcessor = qobject_cast<ImageProcessor *>(processor);
    QString imagePath = imageProcessor->imagePath();
    if (d->imagePath != imagePath) {
        d->imagePath = imagePath;
        emit imagePathChanged();
    }
}


}
