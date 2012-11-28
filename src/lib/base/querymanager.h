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

#ifndef QFB_QUERYMANAGER_H
#define QFB_QUERYMANAGER_H

#include "base_global.h"
#include <QtCore/QObject>

class QNetworkReply;
namespace QFB
{

class FriendListReply;
class QueryManagerPrivate;

/**
 * @brief Query manager
 *
 * This class is used to manage queries and provide QFB::AbstractReply
 * based replies. It is a base class that makes the creation of these
 * replies easier, but might not be suited for higher level access.
 */
class QFBBASE_EXPORT QueryManager : public QObject
{
    Q_OBJECT
    /**
     * @short Access token
     */
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit QueryManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~QueryManager();
    /**
     * @brief Access token
     * @return access token.
     */
    QString token() const;
    Q_INVOKABLE QFB::FriendListReply * queryFriends(const QString &graph);
public Q_SLOTS:
    /**
     * @brief Set the access token
     * @param token access token to set.
     */
    void setToken(const QString &token);

signals:
    /**
     * @brief Access token changed
     */
    void tokenChanged();
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<QueryManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(QueryManager)
};

}

#endif // QFB_QUERYMANAGER_H
