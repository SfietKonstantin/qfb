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

/**
 * @file friendlistmodel.cpp
 * @brief Implementation of QFB::FriendListModel
 */

#include "friendlistmodel.h"
#include "abstractloadablemodel_p.h"
#include <QtCore/QDebug>
#include "querymanager.h"
#include "processors/friendlistprocessor.h"
#include "objects/namedobject.h"

namespace QFB
{

/**
 * @internal
 * @brief Sort following friend name
 * @param friend1 first friend.
 * @param friend2 second friend.
 * @return if the first friend is smaller (in the lexicographical sense) to the second.
 */
bool nameSortLesser(const NamedObject *friend1, const NamedObject *friend2)
{
    return friend1->name() < friend2->name();
}

/**
 * @internal
 * @brief Private class for QFB::FriendListModel
 */
class FriendListModelPrivate: public AbstractLoadableModelPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    FriendListModelPrivate(FriendListModel *q);
    QList<NamedObject *> temporaryData;
    /**
     * @internal
     * @brief Data
     */
    QList<NamedObject *> data;
};

FriendListModelPrivate::FriendListModelPrivate(FriendListModel *q):
    AbstractLoadableModelPrivate(q)
{
}

////// End of private class //////

FriendListModel::FriendListModel(QObject *parent):
    AbstractLoadableModel(*(new FriendListModelPrivate(this)), parent)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    setRoleNames(roleNames());
#endif
}

int FriendListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const FriendListModel);
    return d->data.count();
}

QVariant FriendListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const FriendListModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    NamedObject *item = d->data.at(row);

    switch (role) {
    case DataRole:
        return QVariant::fromValue(item);
        break;
    default:
        return QVariant();
        break;
    }
}

void FriendListModel::handleReply(AbstractPagingProcessor *processor)
{
    Q_D(FriendListModel);
    FriendListProcessor *friendListProcessor = qobject_cast<FriendListProcessor *>(processor);
    if (!friendListProcessor) {
        return;
    }

    QList<NamedObject *> friendList = friendListProcessor->friendList();
    if (friendList.isEmpty()) {
        setDoNotHaveNext();
        qSort(d->temporaryData.begin(), d->temporaryData.end(), nameSortLesser);
        beginInsertRows(QModelIndex(), 0, d->temporaryData.count() - 1);
        d->data = d->temporaryData;
        d->temporaryData.clear();
        emit countChanged();
        endInsertRows();
        return;
    }

    foreach (NamedObject *user, friendList) {
        user->setParent(this);
    }

    d->temporaryData.append(friendList);
}

void FriendListModel::clear()
{
    Q_D(FriendListModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    qDeleteAll(d->data);
    emit countChanged();
    endRemoveRows();
}

Request FriendListModel::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryFriendList(graph, arguments);
    }
    return Request();
}

QHash<int, QByteArray> FriendListModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}

#include "moc_friendlistmodel.cpp"
