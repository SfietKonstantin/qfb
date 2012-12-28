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

#ifndef QFB_ABSTRACTGRAPHPAGINATEDREPLY_P_H
#define QFB_ABSTRACTGRAPHPAGINATEDREPLY_P_H

#include "abstractgraphreply_p.h"

namespace QFB
{

class AbstractGraphPagingReply;
class AbstractGraphPagingReplyPrivate: public AbstractGraphReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    AbstractGraphPagingReplyPrivate(AbstractGraphPagingReply *q);
    QString nextPageGraph;
    QString nextPageArguments;
private:
    Q_DECLARE_PUBLIC(AbstractGraphPagingReply)
};

}

#endif // QFB_ABSTRACTGRAPHPAGINATEDREPLY_P_H
