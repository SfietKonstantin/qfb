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

/**
 * @file objectlistprocessor.h
 * @brief Definition of QFB::ObjectListProcessor
 */

#include "abstractpagingprocessor.h"

namespace QFB
{

class Object;
class ObjectListProcessorPrivate;
/**
 * @brief Processor used to get a list of object
 *
 * This processor is used to get a list of Facebook entity, that
 * are represented as a list of QFB::Object. As with
 * QFB::ObjectProcessor, this class make use of
 * the type of object that is requested to determine what kind
 * of object it is, and can return a specialized subclass of
 * QFB::Object.
 *
 * Note that the type() field of the objects are never set.
 * @todo set that field.
 */
class QFBBASE_EXPORT ObjectListProcessor: public AbstractPagingProcessor
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit ObjectListProcessor(QObject *parent = 0);
    /**
     * @brief List of objects
     * @return list of object.
     */
    QList<Object *> objectList() const;
protected:
    /**
     * @brief Implementation of AbstractProcessor::processDataSource()
     * @param data data to be posted.
     * @return processed data.
     */
    bool processDataSource(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(ObjectListProcessor)
};

}

#endif // QFB_OBJECTLISTPROCESSOR_H
