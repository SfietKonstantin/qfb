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

#include "querymanager.h"
#include "userbase.h"
#include "friendlistreply.h"

namespace QFB
{

/**
 * @internal
 * @brief Sort following friend name
 * @param friend1 first friend.
 * @param friend2 second friend.
 * @return if the first friend is smaller (in the lexicographical sense) to the second.
 */
bool nameSortLesser(const UserBase *friend1, const UserBase *friend2)
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
    /**
     * @internal
     * @brief Implementation of AbstractLoadableModelPrivate::processReply()
     * @param reply reply to be processed.
     * @return if the process is successful.
     */
    bool processReply(const AbstractReply *reply);
    /**
     * @internal
     * @brief Data
     */
    QList<UserBase *> data;
private:
    Q_DECLARE_PUBLIC(FriendListModel)
};

FriendListModelPrivate::FriendListModelPrivate(FriendListModel *q):
    AbstractLoadableModelPrivate(q)
{
}

bool FriendListModelPrivate::processReply(const AbstractReply *reply)
{
    Q_Q(FriendListModel);

    const FriendListReply *friendListReply = qobject_cast<const FriendListReply *>(reply);
    if (!friendListReply) {
        return false;
    }

    // Clean old data
    if (!data.isEmpty()) {
        q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
        data.clear();
        q->endInsertRows();
    }

    data = friendListReply->friendList();
    qSort(data.begin(), data.end(), nameSortLesser);
    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();
    return true;
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

    UserBase *item = d->data.at(row);

    switch (role) {
    case DataRole:
        return QVariant::fromValue(item);
        break;
    default:
        return QVariant();
        break;
    }
}

AbstractReply * FriendListModel::createReply(const QString &graph, const QString &arguments)
{
    return queryManager()->queryFriendList(graph, arguments);
}

QHash<int, QByteArray> FriendListModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}

#include "moc_friendlistmodel.cpp"
