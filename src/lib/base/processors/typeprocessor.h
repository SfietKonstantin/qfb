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

#ifndef QFB_TYPEPROCESSOR_H
#define QFB_TYPEPROCESSOR_H

/**
 * @file typeprocessor.h
 * @brief Definition of QFB::TypeProcessor
 */

#include "abstractgraphprocessor.h"

namespace QFB
{

class Object;
class TypeProcessorPrivate;

/**
 * @brief Processor used to get a type
 *
 * This processor is used to get the type of an object.
 * It returns the identified type as an object that have
 * the type field filled correctly. This object can
 * be accessed through object().
 */
class QFBBASE_EXPORT TypeProcessor: public AbstractGraphProcessor
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit TypeProcessor(QObject *parent = 0);
    /**
     * @brief Object with type
     * @return object with type.
     */
    Object * object() const;
protected:
    /**
     * @brief Reimplementation of AbstractGraphProcessor::processGraphAndArguments()
     * @param graph  graph to be processed.
     * @param arguments arguments to be processed.
     * @return if the graph processing task is successful.
     */
    bool processGraphAndArguments(const QString &graph, const QList<ArgumentPair> &arguments);
    /**
     * @brief Implementation of AbstractProcessor::processDataSource()
     * @param data data to be posted.
     * @return processed data.
     */
    bool processDataSource(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(TypeProcessor)
};

}

#endif // QFB_TYPEPROCESSOR_H
