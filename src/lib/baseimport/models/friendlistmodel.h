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

/**
 * @file friendlistmodel.h
 * @brief Definition of QFB::FriendListModel
 */

#include "abstractloadablemodel.h"

namespace QFB
{

class QueryManager;
class FriendListModelPrivate;

/**
 * @brief Model for a list of friends
 *
 * This model is used to present a list of friends. It uses a
 * QFB::QueryManager to perform operations, and
 * stores the retrived informations in a model.
 *
 * After setting a query manager, calling request()
 * to get a the list of friends.
 */
class QFBBASEIMPORT_EXPORT FriendListModel: public AbstractLoadableModel
{
    Q_OBJECT
public:
    /**
     * @short Model roles
     */
    enum FriendListModelRole {
        /**
         * @short Data role
         */
        DataRole = Qt::UserRole + 1
    };
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit FriendListModel(QObject *parent = 0);
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
    void handleReply(AbstractPagingProcessor *processor, LoadMoreOperation operation);
    void clear();
    Query createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Role names
     * @return role names.
     */
    QHash<int, QByteArray> roleNames() const;
private:
    Q_DECLARE_PRIVATE(FriendListModel)
};

}

#endif // QFB_FRIENDLISTMODEL_H
