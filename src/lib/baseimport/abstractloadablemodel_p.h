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

#ifndef QFB_ABSTRACTLOADABLEMODEL_P_H
#define QFB_ABSTRACTLOADABLEMODEL_P_H

/**
 * @internal
 * @file abstractloadablemodel_p.h
 * @brief Definition of QFB::AbstractLoadableModelPrivate
 */

#include <QtCore/QtGlobal>
#include "request.h"

namespace QFB
{

class AbstractProcessor;
class QueryManager;
class AbstractLoadableModel;
/**
 * @internal
 * @brief Private class for QFB::AbstractLoadableModel
 *
 * This class is a base class for all private class for
 * models that have to load content from Facebook. In order
 * to implementa subclass, processReply() should be implemented.
 */
class AbstractLoadableModelPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    AbstractLoadableModelPrivate(AbstractLoadableModel *q);
    /**
     * @internal
     * @brief Destructor
     */
    virtual ~AbstractLoadableModelPrivate();
protected:
    /**
     * @internal
     * @brief Q-pointer
     */
    AbstractLoadableModel * const q_ptr;
private:
    /**
     * @internal
     * @brief Slot when the request is finished
     */
    void slotFinished(const QFB::Request &request, AbstractProcessor *processor);
    /**
     * @internal
     * @brief Slot when the request failed
     */
    void slotError(const QFB::Request &request, const QString &errorString);
    /**
     * @internal
     * @brief Query manager
     */
    QueryManager *queryManager;
    Request currentRequest;
    QString error;
    QString nextPageGraph;
    QString nextPageArguments;
    bool haveNext;
    bool loading;
    bool autoLoadNext;
    Q_DECLARE_PUBLIC(AbstractLoadableModel)
};

}

#endif // QFB_ABSTRACTLOADABLEMODEL_P_H
