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


#ifndef QFB_COMMENTLISTMODEL_H
#define QFB_COMMENTLISTMODEL_H

/**
 * @file commentlistmodel.h
 * @brief Definition of QFB::CommentListModel
 */

#include "abstractloadablemodel.h"

namespace QFB
{

class QueryManager;
class CommentListModelPrivate;

/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT CommentListModel: public AbstractLoadableModel
{
    Q_OBJECT
public:
    /**
     * @short Model roles
     */
    enum CommentListModelRole {
        /**
        * @short Data role
        */
        DataRole = Qt::UserRole + 1
    };
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit CommentListModel(QObject *parent = 0);
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
    /**
     * @brief Implementation of AbstractLoadableModel::clear()
     */
    void clear();
    /**
     * @brief Reimplementation of AbstractLoadableModel::createRequest()
     * @param graph Graph.
     * @param arguments Arguments.
     * @return Created request.
     */
    Query createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Implementation of AbstractLoadableModel::handleReply()
     * @param processor Processor to handle.
     */
    void handleReply(AbstractPagingProcessor *processor, LoadMoreOperation operation);
    /**
     * @brief Role names
     * @return role names.
     */
    QHash<int, QByteArray> roleNames() const;
private:
    Q_DECLARE_PRIVATE(CommentListModel)
};

}

#endif // COMMENTLISTMODEL_H
