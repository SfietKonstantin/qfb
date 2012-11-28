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

#ifndef QFB_FRIENDLISTREPLY_H
#define QFB_FRIENDLISTREPLY_H

/**
 * @file friendlistreply.h
 * @brief Definition of QFB::FriendListReply
 */

#include "abstractreply.h"

namespace QFB
{

class FriendBase;
class FriendListReplyPrivate;
/**
 * @brief Reply containing the friend list
 *
 * This class subclasses AbstractReply, making it be able to parse
 * friend lists.
 */
class FriendListReply: public AbstractReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit FriendListReply(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~FriendListReply();
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit FriendListReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    /**
     * @brief Friend list
     * @return friend list.
     */
    Q_INVOKABLE QList<FriendBase *> friendList() const;
protected:
    /**
     * @brief Implementation of AbstractReply::processData()
     * @param dataSource data source.
     * @return if the process is successful.
     */
    bool processData(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(FriendListReply)
};

}

Q_DECLARE_METATYPE(QFB::FriendListReply *)

#endif // QFB_FRIENDLISTREPLY_H
