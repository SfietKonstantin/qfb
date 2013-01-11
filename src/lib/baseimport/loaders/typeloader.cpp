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

#include "typeloader.h"
#include "private/abstractloader_p.h"
#include "querymanager.h"
#include "objects/object.h"
#include "processors/typeprocessor.h"

namespace QFB
{

class TypeLoaderPrivate: public AbstractLoaderPrivate
{
public:
    TypeLoaderPrivate(TypeLoader *q);
    Object * object;
};

TypeLoaderPrivate::TypeLoaderPrivate(TypeLoader *q):
    AbstractLoaderPrivate(q)
{
    object = 0;
}

////// End of private class //////

TypeLoader::TypeLoader(QObject *parent) :
    AbstractGraphLoader(*(new TypeLoaderPrivate(this)), parent)
{
}

Object * TypeLoader::object() const
{
    Q_D(const TypeLoader);
    return d->object;
}

Request TypeLoader::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryType(graph, arguments);
    }
    return Request();
}

void TypeLoader::handleReply(AbstractProcessor *processor)
{
    Q_D(TypeLoader);
    TypeProcessor *typeProcessor = qobject_cast<TypeProcessor *>(processor);
    if (d->object) {
        d->object->deleteLater();
    }

    d->object = typeProcessor->object();
    d->object->setParent(this);
    emit objectChanged();
}

}
