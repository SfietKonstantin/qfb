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

#ifndef QFB_USERREPLY_H
#define QFB_USERREPLY_H

/**
 * @file userreply.h
 * @brief Definition of QFB::UserReply
 */

#include "abstractreply.h"

namespace QFB
{

class User;
class UserReplyPrivate;
/**
 * @brief Reply containing an user
 *
 * This class subclasses AbstractReply, making it be able to get
 * users. This reply, when finished, will create an user that
 * have this reply as parent.
 *
 * You can choose the fields of the user you want using
 * the fields query parameter:
 *
 * @code
 * fields=id,name
 * @endcode
 *
 * @todo Allow the user not to have this reply as parent.
 */
class QFBBASE_EXPORT UserReply : public AbstractReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit UserReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit UserReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    /**
     * @brief User
     * @return user.
     */
    User * user() const;
    /**
     * @brief Implementation of AbstractReply::processData()
     * @param dataSource data source.
     * @return if the process is successful.
     */
    bool processData(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(UserReply)
};

}

#endif // QFB_USERREPLY_H
