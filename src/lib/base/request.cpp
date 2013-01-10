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

#include "request.h"
#include "helper_p.h"

namespace QFB
{

Request::Request():
    d_ptr(new RequestPrivate)
{
    setId(-1);
    setType(InvalidRequest);
}

Request::Request(int id, RequestType type):
    d_ptr(new RequestPrivate)
{
    setId(id);
    setType(type);
}

Request::Request(const Request &other):
    d_ptr(other.d_ptr)
{
}

Request::~Request()
{
}

bool Request::operator==(const Request &other) const
{
    Q_D(const Request);
    return (d->id == other.id() && d->type == other.type());
}

bool Request::operator !=(const Request &other) const
{
    Q_D(const Request);
    return (d->id != other.id() || d->type != other.type());
}

bool Request::isValid() const
{
    Q_D(const Request);
    return (d->id != -1 && d->type != InvalidRequest);
}

int Request::id() const
{
    Q_D(const Request);
    return d->id;
}

QUrl Request::url() const
{
    Q_D(const Request);
    return d->url;
}

QString Request::graph() const
{
    Q_D(const Request);
    return d->graph;
}

QList<ArgumentPair> Request::arguments() const
{
    Q_D(const Request);
    return d->arguments;
}

RequestType Request::type() const
{
    Q_D(const Request);
    return d->type;
}

void Request::setId(int id)
{
    Q_D(Request);
    d->id = id;
}

void Request::setUrl(const QUrl &url)
{
    Q_D(Request);
    d->url = url;
}

void Request::setGraph(const QString &graph)
{
    Q_D(Request);
    d->graph = graph;
}

void Request::setArguments(const QString &arguments)
{
    setArguments(createArguments(arguments));
}

void Request::setArguments(const QList<ArgumentPair> &arguments)
{
    Q_D(Request);
    d->arguments = arguments;
}

void Request::setType(RequestType type)
{
    Q_D(Request);
    d->type = type;
}

}
