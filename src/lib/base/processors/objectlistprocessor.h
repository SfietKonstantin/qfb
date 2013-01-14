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

#ifndef QFB_OBJECTLISTPROCESSOR_H
#define QFB_OBJECTLISTPROCESSOR_H

#include "abstractpagingprocessor.h"

namespace QFB
{

class Object;
class ObjectListProcessorPrivate;
class QFBBASE_EXPORT ObjectListProcessor: public AbstractPagingProcessor
{
    Q_OBJECT
public:
    explicit ObjectListProcessor(QObject *parent = 0);
    QList<Object *> objectList() const;
protected:
    bool processDataSource(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(ObjectListProcessor)
};

}

#endif // QFB_OBJECTLISTPROCESSOR_H
