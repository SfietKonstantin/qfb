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

#include "userloader.h"
#include "loaderbase_p.h"

#include "user.h"
#include "userreply.h"
#include "querymanager.h"

#include <QtCore/QDebug>

namespace QFB
{

class UserLoaderPrivate: public LoaderBasePrivate
{
public:
    UserLoaderPrivate(UserLoader *q);
    User *user;
    bool checkReply(const AbstractReply *reply);
    void processReply(const AbstractReply *reply);
private:
    Q_DECLARE_PUBLIC(UserLoader)
};

UserLoaderPrivate::UserLoaderPrivate(UserLoader *q):
    LoaderBasePrivate(q)
{
    user = 0;
}

bool UserLoaderPrivate::checkReply(const AbstractReply *reply)
{
    return qobject_cast<const UserReply *>(reply);
}

void UserLoaderPrivate::processReply(const AbstractReply *reply)
{
    Q_Q(UserLoader);
    if (user) {
        user->deleteLater();
        user = 0;
    }

    const UserReply *userReply = qobject_cast<const UserReply *>(reply);
    User *newUser = userReply->user();

    user = newUser;
    user->setParent(q);
    emit q->userChanged();
}


////// End of private class //////

UserLoader::UserLoader(QObject *parent) :
    AbstractGraphLoader(*(new UserLoaderPrivate(this)), parent)
{
}

User * UserLoader::user() const
{
    Q_D(const UserLoader);
    return d->user;
}

AbstractGraphReply * UserLoader::createReply(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryUser(graph, arguments);
    }
    return 0;
}

}
