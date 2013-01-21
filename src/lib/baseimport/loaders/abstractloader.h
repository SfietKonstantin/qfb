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

#ifndef QFB_ABSTRACTLOADER_H
#define QFB_ABSTRACTLOADER_H

#include <QtCore/QObject>
#include "baseimport_global.h"

namespace QFB
{

class AbstractProcessor;
class QueryManager;
class Query;
class AbstractLoaderPrivate;
class QFBBASEIMPORT_EXPORT AbstractLoader: public QObject
{
    Q_OBJECT
    /**
     * @short Query manager
     */
    Q_PROPERTY(QFB::QueryManager * queryManager READ queryManager WRITE setQueryManager
               NOTIFY queryManagerChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
public:
    explicit AbstractLoader(QObject *parent = 0);
    virtual ~AbstractLoader();
    /**
     * @brief Query manager
     * @return query manager.
     */
    QueryManager * queryManager() const;
    bool loading() const;
    QString error() const;
public Q_SLOTS:
    /**
     * @brief Set the query manager
     * @param queryManager query manager to set.
     */
    void setQueryManager(QueryManager *queryManager);
Q_SIGNALS:
    /**
     * @brief Query manager changed
     */
    void queryManagerChanged();
    void loadingChanged();
    void loaded();
    void errorChanged();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractLoader(AbstractLoaderPrivate &dd, QObject *parent = 0);
    void setLoading(bool loading);
    void handleQuery(const Query &query);
    virtual void handleReply(AbstractProcessor *processor) = 0;
    /**
     * @short D-pointer
     */
    const QScopedPointer<AbstractLoaderPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractLoader)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished(const QFB::Query &query,
                                               AbstractProcessor *processor))
    Q_PRIVATE_SLOT(d_func(), void slotError(const QFB::Query &query,
                                            const QString &errorString))
    /// @endcond
};

}

#endif // QFB_ABSTRACTLOADER_H
