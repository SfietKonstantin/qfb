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

#ifndef QFB_ABSTRACTPREPROCESSOR_H
#define QFB_ABSTRACTPREPROCESSOR_H

#include "base_global.h"
#include <QtCore/QObject>
#include <QtCore/QRunnable>
#include "argumentpair.h"
#include "request.h"

namespace QFB
{

class AbstractPreprocessorPrivate;
class AbstractPreprocessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit AbstractPreprocessor(QObject *parent = 0);
    virtual ~AbstractPreprocessor();
    Request request() const;
    void setRequest(const Request &request);
    void setData(const QString &graph, const QString &arguments);
    QString processedGraph() const;
    QList<ArgumentPair> processedArguments() const;
    void run();
Q_SIGNALS:
    void finished(bool preproce);
protected:
    explicit AbstractPreprocessor(AbstractPreprocessorPrivate &dd, QObject *parent);
    virtual bool processGraphAndArguments(const QString &graph,
                                          const QList<ArgumentPair> &arguments) = 0;
    QScopedPointer<AbstractPreprocessorPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractPreprocessor)
};

}

#endif // ABSTRACTPREPROCESSOR_H
