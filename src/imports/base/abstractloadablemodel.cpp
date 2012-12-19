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

/**
 * @file abstractloadablemodel.cpp
 * @brief Implementation of QFB::AbstractLoadableModel
 */

#include "abstractloadablemodel.h"
#include "abstractloadablemodel_p.h"

#include <QtCore/QDebug>

#include "abstractreply.h"

namespace QFB
{

AbstractLoadableModelPrivate::AbstractLoadableModelPrivate(AbstractLoadableModel *q):
    q_ptr(q)
{
    queryManager = 0;
    reply = 0;
    newReply = 0;
}

AbstractLoadableModelPrivate::~AbstractLoadableModelPrivate()
{
}

void AbstractLoadableModelPrivate::slotFinished()
{
    if (!processReply(newReply)) {
        newReply->deleteLater();
        newReply = 0;
        return;
    }

    if (reply) {
        reply->deleteLater();
    }
    reply = newReply;
    newReply = 0;
}

void AbstractLoadableModelPrivate::slotFailed()
{
    qDebug() << newReply->error();
    newReply->deleteLater();
    newReply = 0;
}

////// End of private class //////

AbstractLoadableModel::AbstractLoadableModel(AbstractLoadableModelPrivate &dd, QObject *parent):
    QAbstractListModel(parent), d_ptr(&dd)
{
}

AbstractLoadableModel::~AbstractLoadableModel()
{
}

int AbstractLoadableModel::count() const
{
    return rowCount();
}

QueryManager * AbstractLoadableModel::queryManager() const
{
    Q_D(const AbstractLoadableModel);
    return d->queryManager;
}

void AbstractLoadableModel::setQueryManager(QueryManager *queryManager)
{
    Q_D(AbstractLoadableModel);
    if (d->queryManager != queryManager) {
        d->queryManager = queryManager;
        emit queryManagerChanged();
    }
}

void AbstractLoadableModel::request(const QString &graph, const QString &arguments)
{
    Q_D(AbstractLoadableModel);
    if (!d->queryManager) {
        return;
    }
    if (d->newReply) {
        return;
    }

    d->newReply = createReply(graph, arguments);
    connect(d->newReply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->newReply, SIGNAL(failed()), this, SLOT(slotFailed()));
}

}

#include "moc_abstractloadablemodel.cpp"
