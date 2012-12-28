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

#ifndef QFB_ABSTRACTGRAPHPAGINGREPLY_H
#define QFB_ABSTRACTGRAPHPAGINGREPLY_H

#include "abstractgraphreply.h"

namespace QFB
{
class AbstractGraphPagingReplyPrivate;
class QFBBASE_EXPORT AbstractGraphPagingReply: public AbstractGraphReply
{
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit AbstractGraphPagingReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractGraphPagingReply(QNetworkAccessManager *networkAccessManager,
                                         QObject *parent = 0);
    QString nextPageGraph() const;
    QString nextPageArguments() const;
protected:
    /**
     * @brief D-pointer constructor
     * @param dd D-pointer.
     * @param parent parent object.
     */
    explicit AbstractGraphPagingReply(AbstractGraphReplyPrivate &dd, QObject *parent = 0);
    void setNextPageUrl(const QUrl &url);
private:
    Q_DECLARE_PRIVATE(AbstractGraphPagingReply)
};

}

#endif // QFB_ABSTRACTGRAPHPAGINGREPLY_H
