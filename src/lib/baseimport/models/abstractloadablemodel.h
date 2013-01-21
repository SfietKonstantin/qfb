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

#ifndef QFB_ABSTRACTLOADABLEMODEL_H
#define QFB_ABSTRACTLOADABLEMODEL_H

/**
 * @file abstractloadablemodel.h
 * @brief Definition of QFB::AbstractLoadableModel
 */

#include "baseimport_global.h"
#include <QtCore/QAbstractListModel>
#include "query.h"

namespace QFB
{

class AbstractPagingProcessor;
class QueryManager;
class AbstractLoadableModelPrivate;
/**
 * @brief Base class for all models that are based on loadable content
 *
 * This model is a base class for models that have to load content
 * from Facebook. It provides a query manager, that should be set and
 * accessed with the queryManager() property, as well as some
 * preimplemented methods, such as request().
 *
 * In order to implement a subclass, createReply() should be
 * implemented, in order to create replies, and both QAbstractListModel::rowCount()
 * and QAbstractListModel::data() should be implemented as well. Methods from the private
 * class, QFB::AbstractLoadableModelPrivate should also be implemented.
 */
class QFBBASEIMPORT_EXPORT AbstractLoadableModel : public QAbstractListModel
{
    Q_OBJECT
    /**
     * @short Count
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    /**
     * @short Query manager
     */
    Q_PROPERTY(QFB::QueryManager * queryManager READ queryManager WRITE setQueryManager
               NOTIFY queryManagerChanged)
    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)
    Q_PROPERTY(bool havePrevious READ havePrevious NOTIFY havePreviousChanged)
    Q_PROPERTY(bool haveNext READ haveNext NOTIFY haveNextChanged)
    Q_PROPERTY(bool autoLoadNext READ autoLoadNext WRITE setAutoLoadNext
               NOTIFY autoLoadNextChanged)
public:
    enum LoadMoreOperation {
        InvalidLoadOperation,
        LoadNextOperation,
        LoadPreviousOperation
    };
    /**
     * @brief Destructor
     */
    virtual ~AbstractLoadableModel();
    /**
     * @short Count
     * @return number of rows in this model.
     */
    int count() const;
    /**
     * @brief Query manager
     * @return query manager.
     */
    QueryManager * queryManager() const;
    bool loading() const;
    QString error() const;
    bool havePrevious() const;
    bool haveNext() const;
    bool autoLoadNext() const;
public Q_SLOTS:
    /**
     * @brief Set the query manager
     * @param queryManager query manager to set.
     */
    void setQueryManager(QueryManager *queryManager);
    void setAutoLoadNext(bool autoLoadNext);
    void loadPrevious();
    void loadNext();
    /**
     * @brief Perform a request
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     */
    void request(const QString &graph, const QString &arguments = QString());
Q_SIGNALS:
    /**
     * @short Count changed
     */
    void countChanged();
    /**
     * @brief Query manager changed
     */
    void queryManagerChanged();
    void loadingChanged();
    void loaded();
    void errorChanged();
    void havePreviousChanged();
    void haveNextChanged();
    void autoLoadNextChanged();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractLoadableModel(AbstractLoadableModelPrivate &dd, QObject *parent = 0);
    void setDoNotHaveMore();
    virtual void handleReply(AbstractPagingProcessor *processor, LoadMoreOperation operation) = 0;
    virtual void clear() = 0;
    virtual Query createRequest(const QString &graph, const QString &arguments = QString()) = 0;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    /**
     * @brief Role names
     * @return role names.
     */
    virtual QHash<int, QByteArray> roleNames() const = 0;
#endif
    /**
     * @short D-pointer
     */
    const QScopedPointer<AbstractLoadableModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractLoadableModel)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished(const QFB::Query &request,
                                               AbstractProcessor *processor))
    Q_PRIVATE_SLOT(d_func(), void slotError(const QFB::Query &request,
                                            const QString &errorString))
    /// @endcond
};

}

#endif // QFB_ABSTRACTLOADABLEMODEL_H
