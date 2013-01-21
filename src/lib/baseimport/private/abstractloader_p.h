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

#ifndef QFB_ABSTRACTLOADER_P_H
#define QFB_ABSTRACTLOADER_P_H

#include <QtCore/QtGlobal>
#include "query.h"

class QString;
namespace QFB
{

class QueryManager;
class AbstractReply;
class AbstractLoader;
class AbstractLoaderPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    AbstractLoaderPrivate(AbstractLoader *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~AbstractLoaderPrivate();
protected:
    /**
     * @internal
     * @brief Q-pointer
     */
    AbstractLoader * const q_ptr;
private:
    /**
     * @internal
     * @brief Slot when the request is finished
     */
    void slotFinished(const QFB::Query &query, QFB::AbstractProcessor *processor);
    /**
     * @internal
     * @brief Slot when the request failed
     */
    void slotError(const QFB::Query &query, const QString &errorString);
    /**
     * @internal
     * @brief Query manager
     */
    QueryManager *queryManager;
    /**
     * @internal
     * @brief Reply
     */
    Query currentQuery;
    bool loading;
    QString error;
    Q_DECLARE_PUBLIC(AbstractLoader)
};


}

#endif // QFB_ABSTRACTLOADER_P_H
