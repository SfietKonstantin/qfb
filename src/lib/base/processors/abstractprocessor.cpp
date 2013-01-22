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
 * @file abstractprocessor.cpp
 * @brief Implementation of QFB::AbstractProcessor
 */

#include "abstractprocessor.h"
#include <QtCore/QDebug>
#include "private/abstractprocessor_p.h"

namespace QFB
{

AbstractProcessorPrivate::AbstractProcessorPrivate()
{
    processingTask = AbstractProcessor::NoProcessing;
    needLoading = true;
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

Query AbstractProcessor::query() const
{
    Q_D(const AbstractProcessor);
    return d->query;
}

QString AbstractProcessor::errorString() const
{
    Q_D(const AbstractProcessor);
    return d->error;
}

void AbstractProcessor::run()
{
    Q_D(AbstractProcessor);
    if (!d->query.isValid()) {
        qWarning() << "Warning: the query is not valid";
        setError(tr("The query is not valid"));
        emit error();
        return;
    }

    PreprocessorData &preprocessorData = d->query.preprocessorData();
    bool ok = false;
    switch (d->processingTask) {
    case Preprocessing:
        preprocessorData.setPostData(processPostData(preprocessorData.data()));
        ok = preprocess();
        if (ok) {
            emit preprocessingFinished(d->needLoading);
        } else {
            emit error();
        }
        break;
    case PostProcessing:
        if (!d->dataSource) {
            qWarning() << "Warning: no data source provided";
            setError(tr("No data source provided"));
            emit error();
            return;
        }
        ok = processDataSource(d->dataSource);
        d->dataSource->deleteLater();
        if (ok) {
            emit postProcessingFinished();
        } else {
            emit error();
        }
        break;
    default:
        qWarning() << "Warning: no processing task set";
        setError(tr("No processing task set"));
        emit error();
        return;
    }
}

void AbstractProcessor::setQuery(const Query &query)
{
    Q_D(AbstractProcessor);
    d->query = WritableQuery::createWritableQuery(query);
}

void AbstractProcessor::setProcessingTask(ProcessingTask processingTask)
{
    Q_D(AbstractProcessor);
    d->processingTask = processingTask;
}

void AbstractProcessor::setDataSource(QIODevice *dataSource)
{
    Q_D(AbstractProcessor);
    d->dataSource = dataSource;
}

QByteArray AbstractProcessor::processPostData(const QVariantMap &data)
{
    Q_UNUSED(data)
    return QByteArray();
}

void AbstractProcessor::setNeedLoading(bool needLoading)
{
    Q_D(AbstractProcessor);
    d->needLoading = needLoading;
}

void AbstractProcessor::setError(const QString &error)
{
    Q_D(AbstractProcessor);
    d->error = error;
}

}
