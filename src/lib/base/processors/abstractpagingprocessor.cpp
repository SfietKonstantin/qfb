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
 * @file abstractpagingprocessor.cpp
 * @brief Implementation of QFB::AbstractPagingProcessor
 */

#include "abstractpagingprocessor.h"
#include <QtCore/QDebug>
#include <QtCore/QString>
#include "private/abstractpagingprocessor_p.h"
#include "private/helper_p.h"

namespace QFB
{

AbstractPagingProcessorPrivate::AbstractPagingProcessorPrivate():
    AbstractGraphProcessorPrivate()
{
}

inline QString extractGraph(const QUrl &url)
{
    return url.path();
}

inline QString extractArguments(const QUrl &url)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QListIterator<QPair<QString, QString> > queryItemsIterator =
            QListIterator<QPair<QString, QString> >(url.queryItems());
#else
    QUrlQuery urlQuery = QUrlQuery(url);
    QListIterator<QPair<QString, QString> > queryItemsIterator =
            QListIterator<QPair<QString, QString> >(urlQuery.queryItems());
#endif
    QStringList parametersList;

    while (queryItemsIterator.hasNext()) {
        QPair<QString, QString> queryItem = queryItemsIterator.next();
        if (queryItem.first != FB_GRAPH_QUERY_TOKEN_KEY) {
            parametersList.append(QString("%1=%2").arg(queryItem.first, queryItem.second));
        }
    }

    return parametersList.join(",");
}

////// End of private class //////

AbstractPagingProcessor::AbstractPagingProcessor(QObject *parent):
    AbstractGraphProcessor(*(new AbstractPagingProcessorPrivate), parent)
{
}

AbstractPagingProcessor::AbstractPagingProcessor(AbstractPagingProcessorPrivate &dd,
                                                 QObject *parent):
    AbstractGraphProcessor(dd, parent)
{
}

QString AbstractPagingProcessor::previousPageGraph() const
{
    Q_D(const AbstractPagingProcessor);
    return d->previousPageGraph;
}

QString AbstractPagingProcessor::previousPageArguments() const
{
    Q_D(const AbstractPagingProcessor);
    return d->previousPageArguments;
}

QString AbstractPagingProcessor::nextPageGraph() const
{
    Q_D(const AbstractPagingProcessor);
    return d->nextPageGraph;
}

QString AbstractPagingProcessor::nextPageArguments() const
{
    Q_D(const AbstractPagingProcessor);
    return d->nextPageArguments;
}

void AbstractPagingProcessor::setPreviousPageUrl(const QUrl &url)
{
    Q_D(AbstractPagingProcessor);
    d->previousPageGraph = extractGraph(url);
    d->previousPageArguments = extractArguments(url);
}

void AbstractPagingProcessor::setNextPageUrl(const QUrl &url)
{
    Q_D(AbstractPagingProcessor);
    d->nextPageGraph = extractGraph(url);
    d->nextPageArguments = extractArguments(url);
}

}
