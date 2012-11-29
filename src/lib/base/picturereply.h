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

#ifndef QFB_PICTUREREPLY_H
#define QFB_PICTUREREPLY_H

#include "abstractreply.h"

namespace QFB
{

class PictureReplyPrivate;
class QFBBASE_EXPORT PictureReply : public AbstractReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit PictureReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit PictureReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    QString picturePath() const;
protected:
    QList<ArgumentPair> processArguments(const QList<ArgumentPair> &arguments);
    bool preprocesssRequest();
    /**
     * @brief Implementation of AbstractReply::processData()
     * @param dataSource data source.
     * @return if the process is successful.
     */
    bool processData(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(PictureReply)
};

}

#endif // PICTUREREPLY_H
