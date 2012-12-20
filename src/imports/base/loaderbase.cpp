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

#include "loaderbase.h"
#include "loaderbase_p.h"

#include <QtCore/QDebug>

#include "abstractreply.h"

namespace QFB
{

LoaderBasePrivate::LoaderBasePrivate(LoaderBase *q):
    q_ptr(q)
{
    queryManager = 0;
    reply = 0;
    newReply = 0;
}

LoaderBasePrivate::~LoaderBasePrivate()
{
}

void LoaderBasePrivate::slotFinished()
{
    if (!checkReply(newReply)) {
        newReply->deleteLater();
        newReply = 0;
        return;
    }

    if (reply) {
        reply->deleteLater();
    }
    reply = newReply;
    newReply = 0;

    processReply(reply);
}

void LoaderBasePrivate::slotFailed()
{
    qDebug() << newReply->error();
    newReply->deleteLater();
    newReply = 0;
}

////// End of private class //////

LoaderBase::LoaderBase(LoaderBasePrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

LoaderBase::~LoaderBase()
{
}

QueryManager * LoaderBase::queryManager() const
{
    Q_D(const LoaderBase);
    return d->queryManager;
}

void LoaderBase::setQueryManager(QueryManager *queryManager)
{
    Q_D(LoaderBase);
    if (d->queryManager != queryManager) {
        d->queryManager = queryManager;
        emit queryManagerChanged();
    }
}

void LoaderBase::setReply(AbstractReply *reply)
{
    Q_D(LoaderBase);
    if (!d->queryManager) {
        return;
    }
    if (d->newReply) {
        return;
    }

    d->newReply = reply;
    connect(d->newReply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->newReply, SIGNAL(failed()), this, SLOT(slotFailed()));
}

}

#include "moc_loaderbase.cpp"
