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

#ifndef QFB_LOADERBASE_P_H
#define QFB_LOADERBASE_P_H

#include <QtCore/QtGlobal>

namespace QFB
{

class QueryManager;
class AbstractReply;
class LoaderBase;
class LoaderBasePrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    LoaderBasePrivate(LoaderBase *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~LoaderBasePrivate();
    virtual bool checkReply(const AbstractReply *reply) = 0;
    /**
     * @internal
     * @brief Process reply
     *
     * This method is used to process a reply from Facebook.
     * It should be implemented in order to fill the model.
     *
     * @param reply reply to be processed.
     * @return if the process is successful.
     */
    virtual void processReply(const AbstractReply *reply) = 0;
protected:
    /**
     * @internal
     * @brief Q-pointer
     */
    LoaderBase * const q_ptr;
private:
    /**
     * @internal
     * @brief Slot when the request is finished
     */
    void slotFinished();
    /**
     * @internal
     * @brief Slot when the request failed
     */
    void slotFailed();
    /**
     * @internal
     * @brief Query manager
     */
    QueryManager *queryManager;
    /**
     * @internal
     * @brief Reply
     */
    AbstractReply *reply;
    /**
     * @internal
     * @brief New reply
     */
    AbstractReply *newReply;
    Q_DECLARE_PUBLIC(LoaderBase)
};

}

#endif // QFB_LOADERBASE_P_H
