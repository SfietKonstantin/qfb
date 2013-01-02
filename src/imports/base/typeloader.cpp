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
#include "loaderbase_p.h"
#include "typereply.h"

#include "querymanager.h"

namespace QFB
{

class TypeLoaderPrivate: public LoaderBasePrivate
{
public:
    TypeLoaderPrivate(TypeLoader *q);
    bool checkReply(const AbstractReply *reply);
    void processReply(const AbstractReply *reply);
    Object * object;
private:
    Q_DECLARE_PUBLIC(TypeLoader)
};

TypeLoaderPrivate::TypeLoaderPrivate(TypeLoader *q):
    LoaderBasePrivate(q)
{
    object = 0;
}

bool TypeLoaderPrivate::checkReply(const AbstractReply *reply)
{
        return qobject_cast<const TypeReply *>(reply);
}

void TypeLoaderPrivate::processReply(const AbstractReply *reply)
{
    Q_Q(TypeLoader);
    if (object) {
        object->deleteLater();
        object = 0;
    }

    const TypeReply *typeReply = qobject_cast<const TypeReply *>(reply);
    Object *newObject = typeReply->object();

    object = newObject;
    object->setParent(q);
    emit q->objectChanged();
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

AbstractGraphReply * TypeLoader::createReply(const QString &graph, const QString &arguments)
{
    return queryManager()->queryType(graph, arguments);
}

}
