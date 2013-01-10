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

#ifndef QFB_ABSTRACTGRAPHPROCESSOR_H
#define QFB_ABSTRACTGRAPHPROCESSOR_H

/**
 * @file abstractgraphprocessor.h
 * @brief Definition of QFB::AbstractGraphProcessor
 */

#include "abstractprocessor.h"

namespace QFB
{

class AbstractGraphProcessorPrivate;
/**
 * @brief Base class for processor for graph based calls
 *
 * This processor is a base class for any processor that
 * make use of Facebook graphs.It provides a way to set
 * an access token and build the url, knowing the graph
 * and arguments.
 *
 * The preprocessing method is also reimplemented in order
 * to provide a graph preprocessing method.
 *
 * @see AbstractProcessor
 */
class QFBBASE_EXPORT AbstractGraphProcessor: public AbstractProcessor
{
    Q_OBJECT
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit AbstractGraphProcessor(QObject *parent = 0);
    /**
     * @brief Set token
     * @param token access token.
     */
    void setToken(const QString &token);
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractGraphProcessor(AbstractGraphProcessorPrivate &dd, QObject *parent);
    /**
     * @brief Process graph and arguments
     *
     * This method is used to perform a preprocessing on the
     * graph and arguments. By default, it do nothing.
     *
     * Reimplement this method in subclasses to perform the
     * preprocessing task. Preprocessed data should be passed
     * to setPreprocessedData().
     *
     * @param graph  graph to be processed.
     * @param arguments arguments to be processed.
     * @return if the graph processing task is successful.
     */
    virtual bool processGraphAndArguments(const QString &graph,
                                          const QList<ArgumentPair> &arguments);
    /**
     * @brief Set preprocessed data
     * @param graph preprocessed graph to set.
     * @param arguments preprocessed arguments to set.
     */
    void setPreprocessedData(const QString &graph, const QList<ArgumentPair> &arguments);
private:
    /**
     * @brief Reimplementation of AbstractProcessor::preprocess()
     * @return if the preprocessing task is successful.
     */
    virtual bool preprocess();
    Q_DECLARE_PRIVATE(AbstractGraphProcessor)
};

}

#endif // QFB_ABSTRACTGRAPHPROCESSOR_H
