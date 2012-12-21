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
 * @file abstractgraphreply.cpp
 * @brief Implementation of QFB::AbstractGraphReply
 */

#include "abstractgraphreply.h"
#include "abstractgraphreply_p.h"
#include "helper_p.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QEvent>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

namespace QFB
{

AbstractGraphReplyPrivate::AbstractGraphReplyPrivate(AbstractGraphReply *q):
    AbstractReplyPrivate(q)
{
}

////// End of private class //////

AbstractGraphReply::AbstractGraphReply(QObject *parent):
    AbstractReply(*(new AbstractGraphReplyPrivate(this)), parent)
{
    Q_D(AbstractGraphReply);
    d->networkAccessManager = 0;
    d->running = false;
}

AbstractGraphReply::AbstractGraphReply(QNetworkAccessManager *networkAccessManager, QObject *parent):
    AbstractReply(*(new AbstractGraphReplyPrivate(this)), parent)
{
    Q_D(AbstractGraphReply);
    d->networkAccessManager = networkAccessManager;
    d->running = false;
}

AbstractGraphReply::AbstractGraphReply(AbstractGraphReplyPrivate &dd, QObject *parent):
    AbstractReply(dd, parent)
{
}

void AbstractGraphReply::request(const QString &graph, const QString &token, const QString &arguments)
{
    Q_D(AbstractGraphReply);
    if (d->reply) {
        return;
    }

    d->graph = graph;

    QStringList argumentList = arguments.split(",");
    QList<ArgumentPair> trueArguments;
    foreach (QString argument, argumentList) {
        QStringList argumentEntriesList = argument.split("=");
        if (argumentEntriesList.count() == 2) {
            ArgumentPair argumentPair;
            argumentPair.first = argumentEntriesList.at(0).trimmed();
            argumentPair.second = argumentEntriesList.at(1).trimmed();
            trueArguments.append(argumentPair);
        }
    }

    d->arguments = processArguments(trueArguments);
    QUrl url = graphUrl(graph, token, d->arguments);
    qDebug() << "Request:" << url;
    get(url);
}

QList<ArgumentPair> AbstractGraphReply::processArguments(const QList<ArgumentPair> &arguments)
{
    return arguments;
}

QString AbstractGraphReply::graph() const
{
    Q_D(const AbstractGraphReply);
    return d->graph;
}

QList<ArgumentPair> AbstractGraphReply::arguments() const
{
    Q_D(const AbstractGraphReply);
    return d->arguments;
}

}

#include "moc_abstractgraphreply.cpp"
