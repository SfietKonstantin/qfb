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
#include "private/abstractloadablemodel_p.h"
#include <QtCore/QDebug>
#include "querymanager.h"
#include "processors/abstractpagingprocessor.h"

namespace QFB
{

AbstractLoadableModelPrivate::AbstractLoadableModelPrivate(AbstractLoadableModel *q):
    q_ptr(q)
{
    queryManager = 0;
    loading = false;
    autoLoadNext = false;
    havePrevious = false;
    haveNext = false;
}

AbstractLoadableModelPrivate::~AbstractLoadableModelPrivate()
{
}

void AbstractLoadableModelPrivate::setLoading(bool loadingToSet)
{
    Q_Q(AbstractLoadableModel);
    if (loading != loadingToSet) {
        loading = loadingToSet;
        emit q->loadingChanged();

        if (!loading) {
            emit q->loaded();
        }
    }
}

void AbstractLoadableModelPrivate::handleQuery(const Query &query)
{
    Q_Q(AbstractLoadableModel);
    if (!query.isValid()) {
        return;
    }

    currentRequest = query;
    if (!error.isEmpty()) {
        error.clear();
        emit q->errorChanged();
    }

    setLoading(true);
}

void AbstractLoadableModelPrivate::slotFinished(const QFB::Query &request,
                                                AbstractProcessor *processor)
{
    Q_Q(AbstractLoadableModel);
    if (request != currentRequest) {
        return;
    }

    AbstractPagingProcessor *pagingProcessor = qobject_cast<AbstractPagingProcessor *>(processor);
    if (!pagingProcessor) {
        return;
    }

    q->handleReply(pagingProcessor, loadMoreOperation);
    pagingProcessor->deleteLater();

    loadMoreOperation = AbstractLoadableModel::InvalidLoadOperation;
    previousPageGraph = QString();
    previousPageArguments = QString();
    nextPageGraph = QString();
    nextPageArguments = QString();

    if (havePrevious) {
        previousPageGraph = pagingProcessor->previousPageGraph();
        previousPageArguments = pagingProcessor->previousPageArguments();
    }

    if (haveNext) {
        nextPageGraph = pagingProcessor->nextPageGraph();
        nextPageArguments = pagingProcessor->nextPageArguments();

        if (autoLoadNext) {
            q->loadNext();
            return;
        }
    }
    setLoading(false);
}

void AbstractLoadableModelPrivate::slotError(const QFB::Query &request,
                                             const QString &errorString)
{
    Q_Q(AbstractLoadableModel);
    if (request != currentRequest) {
        return;
    }

    if (error != errorString) {
        error = errorString;
        emit q->errorChanged();
    }

    q->setDoNotHaveMore();
    setLoading(false);
    loadMoreOperation = AbstractLoadableModel::InvalidLoadOperation;
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

QString AbstractLoadableModel::error() const
{
    Q_D(const AbstractLoadableModel);
    return d->error;
}

bool AbstractLoadableModel::havePrevious() const
{
    Q_D(const AbstractLoadableModel);
    return d->havePrevious;
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
        // Disconnect before
        if (d->queryManager) {
            disconnect(d->queryManager, 0, this, 0);
        }

        d->queryManager = queryManager;
        connect(d->queryManager, SIGNAL(finished(QFB::Query,AbstractProcessor*)),
                this, SLOT(slotFinished(QFB::Query,AbstractProcessor*)));
        connect(d->queryManager, SIGNAL(error(QFB::Query,QString)),
                this, SLOT(slotError(QFB::Query,QString)));
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
    if (!queryManager()) {
        return;
    }
    if (loading()) {
        return;
    }

    clear();
    d->loadMoreOperation = InvalidLoadOperation;
    d->havePrevious = true;
    d->haveNext = true;
    emit haveNextChanged();
    emit havePreviousChanged();

    d->handleQuery(createRequest(graph, arguments));
}

void AbstractLoadableModel::loadPrevious()
{
    Q_D(AbstractLoadableModel);
    if (!d->queryManager) {
        return;
    }
    if (!d->haveNext) {
        return;
    }

    d->loadMoreOperation = LoadPreviousOperation;
    d->handleQuery(createRequest(d->previousPageGraph, d->previousPageArguments));
}

void AbstractLoadableModel::loadNext()
{
    Q_D(AbstractLoadableModel);
    if (!d->queryManager) {
        return;
    }
    if (!d->haveNext) {
        return;
    }

    d->loadMoreOperation = LoadNextOperation;
    d->handleQuery(createRequest(d->nextPageGraph, d->nextPageArguments));
}

void AbstractLoadableModel::setDoNotHaveMore()
{
    Q_D(AbstractLoadableModel);
    switch(d->loadMoreOperation) {
    case LoadNextOperation:
        d->haveNext = false;
        emit haveNextChanged();
        break;
    case LoadPreviousOperation:
        d->havePrevious = false;
        emit havePreviousChanged();
        break;
    default:
        break;
    }
}

}

#include "moc_abstractloadablemodel.cpp"
