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
#include "loaderbase_p.h"

#include "imagereply.h"
#include "querymanager.h"

namespace QFB
{

class ImageLoaderPrivate: public LoaderBasePrivate
{
public:
    ImageLoaderPrivate(ImageLoader *q);
    QString imagePath;
    bool checkReply(const AbstractReply *reply);
    void processReply(const AbstractReply *reply);
private:
    Q_DECLARE_PUBLIC(ImageLoader)
};

ImageLoaderPrivate::ImageLoaderPrivate(ImageLoader *q):
    LoaderBasePrivate(q)
{
}

bool ImageLoaderPrivate::checkReply(const AbstractReply *reply)
{
    return qobject_cast<const ImageReply *>(reply);
}

void ImageLoaderPrivate::processReply(const AbstractReply *reply)
{
    Q_Q(ImageLoader);
    const ImageReply *imageReply = qobject_cast<const ImageReply *>(reply);
    if (imagePath != imageReply->imagePath()) {
        imagePath = imageReply->imagePath();
        emit q->imagePathChanged();
    }
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

AbstractReply * ImageLoader::createReply(const QUrl &url)
{
    if (queryManager()) {
        return queryManager()->queryImage(url);
    }
    return 0;
}

}
