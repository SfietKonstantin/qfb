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

#include "userreply.h"
#include "querymanager.h"

#include <QtCore/QDebug>

namespace QFB
{

class UserLoaderPrivate
{
public:
    UserLoaderPrivate(UserLoader *q);
    void slotFinished();
    void slotFailed();
    QueryManager *queryManager;
    QString picturePath;
    UserReply *reply;
    UserReply *newReply;
private:
    UserLoader * const q_ptr;
    Q_DECLARE_PUBLIC(UserLoader)
};

UserLoaderPrivate::UserLoaderPrivate(UserLoader *q):
    q_ptr(q)
{
    queryManager = 0;
    reply = 0;
    newReply = 0;
}

void UserLoaderPrivate::slotFinished()
{
    Q_Q(UserLoader);
    if (reply) {
        reply->deleteLater();
    }
    reply = newReply;
    newReply = 0;

    emit q->userChanged();
}

void UserLoaderPrivate::slotFailed()
{
    qDebug() << newReply->error();
    newReply->deleteLater();
    newReply = 0;
}

////// End of private class //////

UserLoader::UserLoader(QObject *parent) :
    QObject(parent), d_ptr(new UserLoaderPrivate(this))
{
}

UserLoader::~UserLoader()
{
}

QueryManager * UserLoader::queryManager() const
{
    Q_D(const UserLoader);
    return d->queryManager;
}


User * UserLoader::user() const
{
    Q_D(const UserLoader);
    if (!d->reply) {
        return 0;
    }

    return d->reply->user();
}

void UserLoader::setQueryManager(QueryManager *queryManager)
{
    Q_D(UserLoader);
    if (d->queryManager != queryManager) {
        d->queryManager = queryManager;
        emit queryManagerChanged();

    }
}


void UserLoader::request(const QString &graph, const QString &arguments)
{
    Q_D(UserLoader);

    if (!d->queryManager) {
        return;
    }

    if (d->newReply) {
        return;
    }

    d->newReply = d->queryManager->queryUser(graph, arguments);
    connect(d->newReply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->newReply, SIGNAL(failed()), this, SLOT(slotFailed()));
}

}

#include "moc_userloader.cpp"
