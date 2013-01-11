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

#ifndef QFB_POSTSTATUSPROCESSOR_H
#define QFB_POSTSTATUSPROCESSOR_H

/**
 * @file poststatusprocessor.h
 * @brief Definition of QFB::PostStatusProcessor
 */

#include "abstractgraphprocessor.h"

namespace QFB
{

class Object;
class PostStatusProcessorPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASE_EXPORT PostStatusProcessor: public AbstractGraphProcessor
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit PostStatusProcessor(QObject *parent = 0);
    /**
     * @brief PostStatus
     * @return poststatus.
     */
    Object * reply() const;
protected:
    QByteArray processPostData(const QVariantMap &data);
    bool processDataSource(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(PostStatusProcessor)
};

}

#endif // QFB_POSTSTATUSPROCESSOR_H
