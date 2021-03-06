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

#ifndef QFB_IMAGELOADER_H
#define QFB_IMAGELOADER_H

#include "abstractloader.h"
#include <QtCore/QUrl>

namespace QFB
{

class ImageLoaderPrivate;
class QFBBASEIMPORT_EXPORT ImageLoader: public AbstractLoader
{
    Q_OBJECT
    Q_PROPERTY(QString imagePath READ imagePath NOTIFY imagePathChanged)
public:
    explicit ImageLoader(QObject *parent = 0);
    QString imagePath() const;
public Q_SLOTS:
    void request(const QUrl &url);
Q_SIGNALS:
    void imagePathChanged();
protected:
    Query createRequest(const QUrl &url);
    void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(ImageLoader)
};

}

#endif // QFB_IMAGELOADER_H
