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

#ifndef QFB_FEEDMODEL_H
#define QFB_FEEDMODEL_H

#include "abstractloadablemodel.h"

namespace QFB
{

class QueryManager;
class FeedModelPrivate;
class PostValidator;

/**
 * @brief Model for a feed
 *
 * This model is used to present a feed. It uses a
 * QFB::QueryManager to perform operations, and
 * stores the retrived informations in a model.
 *
 * After setting a query manager, calling request()
 * to get a the list of friends.
 */
class FeedModel: public AbstractLoadableModel
{
    Q_OBJECT
    Q_PROPERTY(QFB::PostValidator * validator READ validator WRITE setValidator
               NOTIFY validatorChanged)
public:
    /**
     * @short Model roles
     */
    enum FeedModelRole {
        /**
         * @short Data role
         */
        DataRole = Qt::UserRole + 1
    };
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit FeedModel(QObject *parent = 0);
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
    PostValidator * validator() const;
public Q_SLOTS:
    void setValidator(PostValidator *validator);
Q_SIGNALS:
    void validatorChanged();
protected:
    void handleReply(AbstractPagingProcessor *processor);
    void clear();
    Request createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Role names
     * @return role names.
     */
    QHash<int, QByteArray> roleNames() const;
private:
    Q_DECLARE_PRIVATE(FeedModel)
};

}

#endif // QFB_FEEDMODEL_H
