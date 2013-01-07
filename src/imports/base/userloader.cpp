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
#include "abstractloader_p.h"

#include "user.h"
#include "userprocessor.h"
#include "querymanager.h"

namespace QFB
{

class UserLoaderPrivate: public AbstractLoaderPrivate
{
public:
    UserLoaderPrivate(UserLoader *q);
    User *user;
private:
    Q_DECLARE_PUBLIC(UserLoader)
};

UserLoaderPrivate::UserLoaderPrivate(UserLoader *q):
    AbstractLoaderPrivate(q)
{
    user = 0;
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

Request UserLoader::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryUser(graph, arguments);
    }
    return Request();
}

void UserLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(UserLoader);
    UserProcessor *userProcessor = qobject_cast<UserProcessor *>(processor);
    if (d->user) {
        d->user->deleteLater();
    }

    d->user = userProcessor->user();
    emit userChanged();

    processor->deleteLater();
}

}
