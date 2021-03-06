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

#include "abstractloader.h"
#include "private/abstractloader_p.h"
#include "processors/abstractprocessor.h"
#include "querymanager.h"


namespace QFB
{

AbstractLoaderPrivate::AbstractLoaderPrivate(AbstractLoader *q):
    q_ptr(q)
{
    queryManager = 0;
    loading = false;
}

AbstractLoaderPrivate::~AbstractLoaderPrivate()
{
}

void AbstractLoaderPrivate::slotFinished(const QFB::Query &query,
                                         AbstractProcessor *processor)
{
    Q_Q(AbstractLoader);
    if (query != currentQuery) {
        return;
    }

    q->handleReply(processor);
    processor->deleteLater();
    q->setLoading(false);
}

void AbstractLoaderPrivate::slotError(const QFB::Query &query, const QString &errorString)
{
    Q_Q(AbstractLoader);
    if (query != currentQuery) {
        return;
    }

    if (error != errorString) {
        error = errorString;
        emit q->errorChanged();
    }

    q->setLoading(false);
}

////// End of private class //////

AbstractLoader::AbstractLoader(QObject *parent):
    QObject(parent), d_ptr(new AbstractLoaderPrivate(this))
{
}

AbstractLoader::AbstractLoader(AbstractLoaderPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

AbstractLoader::~AbstractLoader()
{
}

QueryManager * AbstractLoader::queryManager() const
{
    Q_D(const AbstractLoader);
    return d->queryManager;
}

bool AbstractLoader::loading() const
{
    Q_D(const AbstractLoader);
    return d->loading;
}

QString AbstractLoader::error() const
{
    Q_D(const AbstractLoader);
    return d->error;
}

void AbstractLoader::setQueryManager(QueryManager *queryManager)
{
    Q_D(AbstractLoader);
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

void AbstractLoader::setError(const QString &error)
{
    Q_D(AbstractLoader);
    if (d->error != error) {
        d->error = error;
        emit errorChanged();
    }
}

void AbstractLoader::setLoading(bool loading)
{
    Q_D(AbstractLoader);
    if (d->loading != loading) {
        d->loading = loading;
        emit loadingChanged();

        if (!d->loading) {
            emit loaded(d->error.isEmpty());
        }
    }
}

void AbstractLoader::handleQuery(const Query &query)
{
    Q_D(AbstractLoader);
    d->currentQuery = query;
    if (!d->error.isEmpty()) {
        d->error.clear();
        emit errorChanged();
    }

    setLoading(true);
}

}

#include "moc_abstractloader.cpp"
