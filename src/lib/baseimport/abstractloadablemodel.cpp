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
#include "abstractpagingprocessor.h"
#include "querymanager.h"

namespace QFB
{

AbstractLoadableModelPrivate::AbstractLoadableModelPrivate(AbstractLoadableModel *q):
    q_ptr(q)
{
    queryManager = 0;
    loading = false;
    autoLoadNext = false;
    haveNext = false;
}

AbstractLoadableModelPrivate::~AbstractLoadableModelPrivate()
{
}

void AbstractLoadableModelPrivate::slotFinished(const QFB::Request &request,
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

    q->handleReply(pagingProcessor);
    pagingProcessor->deleteLater();

    nextPageGraph = QString();
    nextPageArguments = QString();

    if (haveNext) {
        nextPageGraph = pagingProcessor->nextPageGraph();
        nextPageArguments = pagingProcessor->nextPageArguments();

        if (autoLoadNext) {
            q->loadNext();
        } else {
            q->setLoading(false);
        }

    } else {
        q->setLoading(false);
    }
}

void AbstractLoadableModelPrivate::slotError(const QFB::Request &request,
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

    q->setLoading(false);
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
        connect(d->queryManager, SIGNAL(finished(QFB::Request,AbstractProcessor*)),
                this, SLOT(slotFinished(QFB::Request,AbstractProcessor*)));
        connect(d->queryManager, SIGNAL(error(QFB::Request,QString)),
                this, SLOT(slotError(QFB::Request,QString)));
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
    d->haveNext = true;
    emit haveNextChanged();

    Request request = createRequest(graph, arguments);
    if (request.isValid()) {
        handleRequest(request);
    }
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

    Request request = createRequest(d->nextPageGraph, d->nextPageArguments);
    if (request.isValid()) {
        handleRequest(request);
    }
}

void AbstractLoadableModel::handleRequest(const Request &request)
{
    Q_D(AbstractLoadableModel);
    d->currentRequest = request;
    if (!d->error.isEmpty()) {
        d->error.clear();
        emit errorChanged();
    }

    setLoading(true);
}

void AbstractLoadableModel::setLoading(bool loading)
{
    Q_D(AbstractLoadableModel);
    if (d->loading != loading) {
        d->loading = loading;
        emit loadingChanged();

        if (!d->loading) {
            emit loaded();
        }
    }
}

void AbstractLoadableModel::setDoNotHaveNext()
{
    Q_D(AbstractLoadableModel);
    d->haveNext = false;
    emit haveNextChanged();

}

}

#include "moc_abstractloadablemodel.cpp"
