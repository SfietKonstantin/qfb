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

#ifndef QFB_ABSTRACTPROCESSOR_H
#define QFB_ABSTRACTPROCESSOR_H

#include "base_global.h"
#include <QtCore/QObject>
#include <QtCore/QRunnable>

class QIODevice;
namespace QFB
{

class Request;
class AbstractProcessorPrivate;
class QFBBASE_EXPORT AbstractProcessor : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit AbstractProcessor(QObject *parent = 0);
    virtual ~AbstractProcessor();
    Request request() const;
    void setRequest(const Request &request);
    void setDataSource(QIODevice *dataSource);
    QString errorString() const;
    void run();
Q_SIGNALS:
    void error();
    void finished();
protected:
    explicit AbstractProcessor(AbstractProcessorPrivate &dd, QObject *parent);
    virtual bool processDataSource(QIODevice *dataSource) = 0;
    void setError(const QString &error);
    QScopedPointer<AbstractProcessorPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractProcessor)
};

}

#endif // QFB_ABSTRACTPROCESSOR_H
