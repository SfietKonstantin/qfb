/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef QFB_LIKELOADER_H
#define QFB_LIKELOADER_H

#include "abstractgraphloader.h"

namespace QFB
{

class LikeLoaderPrivate;
class QFBBASEIMPORT_EXPORT LikeLoader: public AbstractGraphLoader
{
    Q_OBJECT
    Q_ENUMS(LikeOperation)
    Q_PROPERTY(LikeOperation likeOperation READ likeOperation WRITE setLikeOperation
               NOTIFY likeOperationChanged)
public:
    enum LikeOperation {
        Like, Unlike
    };
    explicit LikeLoader(QObject *parent = 0);
    LikeOperation likeOperation() const;
public Q_SLOTS:
    void setLikeOperation(LikeOperation likeOperation);
Q_SIGNALS:
    void likeOperationChanged();
protected:
    Query createRequest(const QString &graph, const QString &arguments);
    void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(LikeLoader)
};

}

#endif // QFB_LIKELOADER_H
