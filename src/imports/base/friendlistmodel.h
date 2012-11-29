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

#ifndef QFB_FRIENDLISTMODEL_H
#define QFB_FRIENDLISTMODEL_H

#include <QtCore/QAbstractListModel>

namespace QFB
{

class QueryManager;
class FriendListModelPrivate;
class FriendListModel: public QAbstractListModel
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
public:
    /**
     * @short Model roles
     */
    enum WidgetsPageListModelRole {
        /**
         * @short Data role
         */
        DataRole = Qt::UserRole + 1
    };
    explicit FriendListModel(QObject *parent = 0);
    /**
     * @short Destructor
     */
    virtual ~FriendListModel();
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Count
     * @return number of rows in this model.
     */
    int count() const;
    QueryManager * queryManager() const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
public Q_SLOTS:
    void setQueryManager(QueryManager *queryManager);
    /**
     * @brief Perform a request
     * @param graph graph entry of the Facebook graph API.
     */
    void request(const QString &graph);
Q_SIGNALS:
    /**
     * @short Count changed
     */
    void countChanged();
    /**
     * @brief Query manager changed
     */
    void queryManagerChanged();
protected:
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    /**
     * @brief Role names
     * @return role names.
     */
    QHash<int, QByteArray> roleNames() const;
#endif
    /**
     * @short D-pointer
     */
    const QScopedPointer<FriendListModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(FriendListModel)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotFailed())
    /// @endcond
};

}

#endif // QFB_FRIENDLISTMODEL_H
