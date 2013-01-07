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

#include "abstractprocessor.h"
#include "abstractprocessor_p.h"
#include <QtCore/QDebug>
#include "request.h"

namespace QFB
{

AbstractProcessorPrivate::AbstractProcessorPrivate()
{
    dataSource = 0;
}

////// End of private class //////

AbstractProcessor::AbstractProcessor(QObject *parent):
    QObject(parent), QRunnable(), d_ptr(new AbstractProcessorPrivate)
{
}

AbstractProcessor::AbstractProcessor(AbstractProcessorPrivate &dd, QObject *parent):
    QObject(parent), QRunnable(), d_ptr(&dd)
{
}

AbstractProcessor::~AbstractProcessor()
{
}

Request AbstractProcessor::request() const
{
    Q_D(const AbstractProcessor);
    return d->request;
}

void AbstractProcessor::setRequest(const Request &request)
{
    Q_D(AbstractProcessor);
    d->request = request;
}

void AbstractProcessor::setDataSource(QIODevice *dataSource)
{
    Q_D(AbstractProcessor);
    d->dataSource = dataSource;
}

QString AbstractProcessor::errorString() const
{
    Q_D(const AbstractProcessor);
    return d->error;
}

void AbstractProcessor::run()
{
    Q_D(AbstractProcessor);
    if (!d->dataSource) {
        qWarning() << "Warning: no data source provided";
        emit error();
        return;
    }

    if (!d->request.isValid()) {
        qWarning() << "Warning: the request is not valid";
        emit error();
        return;
    }

    if (processDataSource(d->dataSource)) {
        emit finished();
    } else {
        emit error();
    }
    d->dataSource->deleteLater();
}

void AbstractProcessor::setError(const QString &error)
{
    Q_D(AbstractProcessor);
    d->error = error;
}

}
