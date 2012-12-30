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

#include "abstractgraphpagingreply.h"

namespace QFB
{

AbstractLoadableModelPrivate::AbstractLoadableModelPrivate(AbstractLoadableModel *q):
    q_ptr(q)
{
    queryManager = 0;
    reply = 0;
    loading = false;
    autoLoadNext = false;
    haveNext = false;
}

AbstractLoadableModelPrivate::~AbstractLoadableModelPrivate()
{
}

void AbstractLoadableModelPrivate::setDoNotHaveNext()
{
    Q_Q(AbstractLoadableModel);
    haveNext = false;
    emit q->haveNextChanged();
}

void AbstractLoadableModelPrivate::slotFinished()
{
    Q_Q(AbstractLoadableModel);
    bool ok = processReply(reply);
    nextPageGraph = QString();
    nextPageArguments = QString();
    if (ok) {
        nextPageGraph = reply->nextPageGraph();
        nextPageArguments = reply->nextPageArguments();
    }
    reply->deleteLater();
    reply = 0;

    if (!ok) {
        return;
    }

    if (autoLoadNext) {
        q->loadNext();
    }
    loading = false;
    emit q->loadingChanged();
}

void AbstractLoadableModelPrivate::slotFailed()
{
    Q_Q(AbstractLoadableModel);

    qDebug() << reply->error();
    reply->deleteLater();
    reply = 0;

    loading = false;
    emit q->loadingChanged();
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

bool AbstractLoadableModel::loading() const
{
    Q_D(const AbstractLoadableModel);
    return d->loading;
}

bool AbstractLoadableModel::haveNext() const
{
    Q_D(const AbstractLoadableModel);
    return d->haveNext;
}

bool AbstractLoadableModel::autoLoadNext() const
{
    Q_D(const AbstractLoadableModel);
    return d->autoLoadNext;
}

void AbstractLoadableModel::setQueryManager(QueryManager *queryManager)
{
    Q_D(AbstractLoadableModel);
    if (d->queryManager != queryManager) {
        d->queryManager = queryManager;
        emit queryManagerChanged();
    }
}

void AbstractLoadableModel::setAutoLoadNext(bool autoLoadNext)
{
    Q_D(AbstractLoadableModel);
    if (d->autoLoadNext != autoLoadNext) {
        d->autoLoadNext = autoLoadNext;
        emit autoLoadNextChanged();
    }
}

void AbstractLoadableModel::request(const QString &graph, const QString &arguments)
{
    Q_D(AbstractLoadableModel);
    if (!d->queryManager) {
        return;
    }
    if (d->reply) {
        return;
    }

    d->clear();
    d->haveNext = true;
    emit haveNextChanged();
    d->reply = createReply(graph, arguments);
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->reply, SIGNAL(failed()), this, SLOT(slotFailed()));
}

void AbstractLoadableModel::loadNext()
{
    Q_D(AbstractLoadableModel);
    if (!d->queryManager) {
        return;
    }
    if (d->reply) {
        return;
    }

    if (!d->haveNext) {
        return;
    }

    d->reply = createReply(d->nextPageGraph, d->nextPageArguments);
    connect(d->reply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->reply, SIGNAL(failed()), this, SLOT(slotFailed()));
    d->loading = true;
    emit loadingChanged();
}

}

#include "moc_abstractloadablemodel.cpp"
