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

#include "abstractgraphprocessor.h"
#include "abstractgraphprocessor_p.h"
#include <QtCore/QDebug>
#include "helper_p.h"

namespace QFB
{

AbstractGraphProcessorPrivate::AbstractGraphProcessorPrivate():
    AbstractProcessorPrivate()
{
}

////// End of private class //////

AbstractGraphProcessor::AbstractGraphProcessor(QObject *parent):
    AbstractProcessor(*(new AbstractGraphProcessorPrivate), parent)
{
}

AbstractGraphProcessor::AbstractGraphProcessor(AbstractGraphProcessorPrivate &dd, QObject *parent):
    AbstractProcessor(dd, parent)
{
}

void AbstractGraphProcessor::setToken(const QString &token)
{
    Q_D(AbstractGraphProcessor);
    d->token = token;
}

bool AbstractGraphProcessor::preprocess()
{
    Q_D(AbstractGraphProcessor);
    if (d->request.graph().isEmpty()) {
        qWarning() << "Warning: the graph is empty";
        setError(tr("The graph is empty"));
        return false;
    }

    bool ok = processGraphAndArguments(d->request.graph(), d->request.arguments());
    if (ok) {
        QUrl url = graphUrl(d->request.graph(), d->token, d->request.arguments());
        d->request.setUrl(url);
    }
    return ok;
}

bool AbstractGraphProcessor::processGraphAndArguments(const QString &graph,
                                                      const QList<ArgumentPair> &arguments)
{
    setPreprocessedData(graph, arguments);
    return true;
}

void AbstractGraphProcessor::setPreprocessedData(const QString &graph,
                                                 const QList<ArgumentPair> &arguments)
{
    Q_D(AbstractGraphProcessor);
    d->request.setGraph(graph);
    d->request.setArguments(arguments);
}

}