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

#include "abstractprocessor.h"

namespace QFB
{

class AbstractGraphProcessorPrivate;
class QFBBASE_EXPORT AbstractGraphProcessor: public AbstractProcessor
{
    Q_OBJECT
public:
    explicit AbstractGraphProcessor(QObject *parent = 0);
    void setToken(const QString &token);
protected:
    explicit AbstractGraphProcessor(AbstractGraphProcessorPrivate &dd, QObject *parent);
    virtual bool processGraphAndArguments(const QString &graph,
                                          const QList<ArgumentPair> &arguments);
    void setPreprocessedData(const QString &graph, const QList<ArgumentPair> &arguments);
private:
    virtual bool preprocess();
    Q_DECLARE_PRIVATE(AbstractGraphProcessor)
};

}

#endif // QFB_ABSTRACTGRAPHPROCESSOR_H
