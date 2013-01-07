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
#include "namedobject.h"
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
    /**
     * @internal
     * @brief Implementation of AbstractLoadableModelPrivate::processReply()
     * @param reply reply to be processed.
     * @return if the process is successful.
     */
    bool processReply(const AbstractGraphPagingReply *reply);
    virtual void clear();
    QList<NamedObject *> temporaryData;
    /**
     * @internal
     * @brief Data
     */
    QList<NamedObject *> data;
private:
    Q_DECLARE_PUBLIC(FriendListModel)
};

FriendListModelPrivate::FriendListModelPrivate(FriendListModel *q):
    AbstractLoadableModelPrivate(q)
{
}

bool FriendListModelPrivate::processReply(const AbstractGraphPagingReply *reply)
{
    Q_Q(FriendListModel);

    const FriendListReply *friendListReply = qobject_cast<const FriendListReply *>(reply);
    if (!friendListReply) {
        return false;
    }

    QList<NamedObject *> friendList = friendListReply->friendList();
    if (friendList.isEmpty()) {
        setDoNotHaveNext();
        qSort(temporaryData.begin(), temporaryData.end(), nameSortLesser);
        q->beginInsertRows(QModelIndex(), q->rowCount(), temporaryData.count() - 1);
        data = temporaryData;
        temporaryData.clear();
        emit q->countChanged();
        q->endInsertRows();
        return true;
    }

    foreach (NamedObject *user, friendList) {
        user->setParent(q);
    }

    temporaryData.append(friendList);

    return true;
}

void FriendListModelPrivate::clear()
{
    Q_Q(FriendListModel);
    if (!data.isEmpty()) {
        q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
        qDeleteAll(data);
        data.clear();
        q->endRemoveRows();
    }
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

AbstractGraphPagingReply *FriendListModel::createReply(const QString &graph,
                                                       const QString &arguments)
{
//    return queryManager()->queryFriendList(graph, arguments);
    return 0;
}

QHash<int, QByteArray> FriendListModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}

#include "moc_friendlistmodel.cpp"
