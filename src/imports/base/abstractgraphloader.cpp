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

#include "abstractgraphloader.h"
#include "abstractgraphreply.h"

#include "request.h"

namespace QFB
{

AbstractGraphLoader::AbstractGraphLoader(QObject *parent):
    AbstractLoader(parent)
{
}

AbstractGraphLoader::AbstractGraphLoader(AbstractLoaderPrivate &dd, QObject *parent):
    AbstractLoader(dd, parent)
{
}

void AbstractGraphLoader::request(const QString &graph, const QString &arguments)
{
    if (!queryManager()) {
        return;
    }

    Request createdRequest = createRequest(graph, arguments);
    if (createdRequest.isValid()) {
        handleRequest(createdRequest);
    }
}

}
