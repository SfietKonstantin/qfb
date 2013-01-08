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

#ifndef QFB_TYPELOADER_H
#define QFB_TYPELOADER_H

#include "abstractgraphloader.h"

namespace QFB
{

class Object;
class TypeLoaderPrivate;
class TypeLoader : public AbstractGraphLoader
{
    Q_OBJECT
    Q_PROPERTY(QFB::Object * object READ object NOTIFY objectChanged)
public:
    explicit TypeLoader(QObject *parent = 0);
    Object * object() const;
Q_SIGNALS:
    void objectChanged();
protected:
    Request createRequest(const QString &graph, const QString &arguments);
    void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(TypeLoader)
};

}

#endif // TYPELOADER_H
