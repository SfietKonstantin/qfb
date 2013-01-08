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

#ifndef QFB_PICTURELOADER_H
#define QFB_PICTURELOADER_H

#include "abstractgraphloader.h"

namespace QFB
{
class PictureLoaderPrivate;
class QFBBASEIMPORT_EXPORT PictureLoader : public AbstractGraphLoader
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString picturePath READ picturePath NOTIFY picturePathChanged)
public:
    enum Type {
        Square,
        Small,
        Normal,
        Large
    };
    explicit PictureLoader(QObject *parent = 0);
    Type type() const;
    QString picturePath() const;
public Q_SLOTS:
    void setType(Type type);
Q_SIGNALS:
    void typeChanged();
    void picturePathChanged();
protected:
    Request createRequest(const QString &graph, const QString &arguments);
    void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(PictureLoader)
};

}

#endif // QFB_PICTURELOADER_H
