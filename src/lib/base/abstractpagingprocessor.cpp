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

#include "abstractpagingprocessor.h"
#include "abstractpagingprocessor_p.h"

#include <QtCore/QString>
#include "helper_p.h"

namespace QFB
{

AbstractPagingProcessorPrivate::AbstractPagingProcessorPrivate():
    AbstractProcessorPrivate()
{
}

////// End of private class //////

AbstractPagingProcessor::AbstractPagingProcessor(QObject *parent):
    AbstractProcessor(*(new AbstractPagingProcessorPrivate), parent)
{
}

AbstractPagingProcessor::AbstractPagingProcessor(AbstractPagingProcessorPrivate &dd,
                                                 QObject *parent):
    AbstractProcessor(dd, parent)
{
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

void AbstractPagingProcessor::setNextPageUrl(const QUrl &url)
{
    Q_D(AbstractPagingProcessor);
    QListIterator<QPair<QString, QString> > queryItemsIterator =
            QListIterator<QPair<QString, QString> >(url.queryItems());

    QStringList parametersList;

    while (queryItemsIterator.hasNext()) {
        QPair<QString, QString> queryItem = queryItemsIterator.next();
        if (queryItem.first != FB_GRAPH_QUERY_TOKEN_KEY) {
            parametersList.append(QString("%1=%2").arg(queryItem.first, queryItem.second));
        }
    }

    d->nextPageGraph = url.path();
    d->nextPageArguments = parametersList.join(",");
}

}
