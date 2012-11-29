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

#ifndef QFB_USERLOADER_H
#define QFB_USERLOADER_H

#include <QtCore/QObject>

namespace QFB
{

class User;
class QueryManager;
class UserLoaderPrivate;
class UserLoader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QFB::QueryManager * queryManager READ queryManager WRITE setQueryManager
               NOTIFY queryManagerChanged)
    Q_PROPERTY(QFB::User * user READ user NOTIFY userChanged)
public:
    explicit UserLoader(QObject *parent = 0);
    virtual ~UserLoader();
    QueryManager * queryManager() const;
    User * user() const;
public Q_SLOTS:
    void setQueryManager(QueryManager *queryManager);
    void request(const QString &graph);
Q_SIGNALS:
    void queryManagerChanged();
    void userChanged();
protected:
    QScopedPointer<UserLoaderPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(UserLoader)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotFailed())
    /// @endcond

};

}

#endif // QFB_USERLOADER_H
