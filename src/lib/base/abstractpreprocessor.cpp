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

#include "abstractpreprocessor.h"
#include "abstractpreprocessor_p.h"
#include "helper_p.h"

namespace QFB
{

AbstractPreprocessorPrivate::AbstractPreprocessorPrivate()
{
}

////// End of private class //////

AbstractPreprocessor::AbstractPreprocessor(QObject *parent) :
    QObject(parent), d_ptr(new AbstractPreprocessorPrivate())
{
}

AbstractPreprocessor::AbstractPreprocessor(AbstractPreprocessorPrivate &dd, QObject *parent):
    QObject(parent), d_ptr(&dd)
{
}

AbstractPreprocessor::~AbstractPreprocessor()
{
}

Request AbstractPreprocessor::request() const
{
    Q_D(const AbstractPreprocessor);
    return d->request;
}

void AbstractPreprocessor::setRequest(const Request &request)
{
    Q_D(AbstractPreprocessor);
    d->request = request;
}

void AbstractPreprocessor::setData(const QString &graph, const QString &arguments)
{
    Q_D(AbstractPreprocessor);
    d->graph = graph;
    d->arguments = createArguments(arguments);
}

QString AbstractPreprocessor::processedGraph() const
{
    Q_D(const AbstractPreprocessor);
    return d->processedGraph;
}

QList<ArgumentPair> AbstractPreprocessor::processedArguments() const
{
    Q_D(const AbstractPreprocessor);
    return d->processedArguments;
}

void AbstractPreprocessor::run()
{
    Q_D(AbstractPreprocessor);
    if (processGraphAndArguments(d->graph, d->arguments)) {
        emit finished();
    } else {

    }
}

}
