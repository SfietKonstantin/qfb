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

#ifndef QFB_IMAGEREPLY_H
#define QFB_IMAGEREPLY_H

#include "abstractreply.h"

namespace QFB
{

class ImageReplyPrivate;
class QFBBASE_EXPORT ImageReply: public AbstractReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit ImageReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit ImageReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    /**
     * @brief Path to picture
     * @return path to the picture.
     */
    QString imagePath() const;
    void request(const QUrl &url);
protected:
    /**
     * @brief Reimplementation of AbstractReply::preprocesssRequest()
     * @return if the process should be performed.
     */
    bool preprocesssRequest();
    /**
     * @brief Implementation of AbstractReply::processData()
     * @param dataSource data source.
     * @return if the process is successful.
     */
    bool processData(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(ImageReply)
};

}

#endif // QFB_IMAGEREPLY_H
