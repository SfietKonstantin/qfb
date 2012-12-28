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

#include "abstractgraphpagingreply.h"
#include "abstractgraphpagingreply_p.h"

#include <QtCore/QDebug>
#include <QtCore/QUrl>

#include "helper_p.h"

namespace QFB
{

AbstractGraphPagingReplyPrivate::AbstractGraphPagingReplyPrivate(AbstractGraphPagingReply *q):
    AbstractGraphReplyPrivate(q)
{
}

////// End of private class //////

AbstractGraphPagingReply::AbstractGraphPagingReply(QObject *parent):
    AbstractGraphReply(*(new AbstractGraphPagingReplyPrivate(this)), parent)
{
    Q_D(AbstractGraphPagingReply);
    d->networkAccessManager = 0;
    d->running = false;
}

AbstractGraphPagingReply
    ::AbstractGraphPagingReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractGraphReply(*(new AbstractGraphPagingReplyPrivate(this)), parent)
{
    Q_D(AbstractGraphPagingReply);
    d->networkAccessManager = networkAccessManager;
    d->running = false;
}

AbstractGraphPagingReply::AbstractGraphPagingReply(AbstractGraphReplyPrivate &dd, QObject *parent):
    AbstractGraphReply(dd, parent)
{
}

QString AbstractGraphPagingReply::nextPageGraph() const
{
    Q_D(const AbstractGraphPagingReply);
    return d->nextPageGraph;
}

QString AbstractGraphPagingReply::nextPageArguments() const
{
    Q_D(const AbstractGraphPagingReply);
    return d->nextPageArguments;
}

void AbstractGraphPagingReply::setNextPageUrl(const QUrl &url)
{
    Q_D(AbstractGraphPagingReply);
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
