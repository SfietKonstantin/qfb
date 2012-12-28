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

#include "abstractgraphpagingreply.h"

namespace QFB
{

class NamedObject;
class FriendListReplyPrivate;
/**
 * @brief Reply containing a list of friends
 *
 * This class subclasses AbstractGraphReply, making it be able to parse
 * friend lists. This reply, when finished, will create a list of users
 * that have this reply as parent.
 *
 * Note that currently, Facebook API do not allow you to access
 * friends of friends, so do not use this class to get friends of
 * friends, it will not work.
 *
 * @todo Allow the users not to have this reply as parent.
 */
class FriendListReply: public AbstractGraphPagingReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit FriendListReply(QObject *parent = 0);
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
    QList<NamedObject *> friendList() const;
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

#endif // QFB_FRIENDLISTREPLY_H
