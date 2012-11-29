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

#include "friendlistmodel.h"
#include "querymanager.h"
#include "userbase.h"
#include "friendlistreply.h"
#include <QtCore/QDebug>

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

class FriendListModelPrivate
{
public:
    FriendListModelPrivate(FriendListModel *q);
    void slotFinished();
    void slotFailed();
    QList<UserBase *> data;
    QueryManager *queryManager;
    FriendListReply *reply;
    FriendListReply *newReply;
private:
    FriendListModel * const q_ptr;
    Q_DECLARE_PUBLIC(FriendListModel)
};

FriendListModelPrivate::FriendListModelPrivate(FriendListModel *q):
    q_ptr(q)
{
    queryManager = 0;
    reply = 0;
    newReply = 0;
}

void FriendListModelPrivate::slotFinished()
{
    Q_Q(FriendListModel);

    // Clean old data
    if (!data.isEmpty()) {
        q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
        data.clear();
        q->endInsertRows();
    }
    if (reply) {
        reply->deleteLater();
    }
    reply = newReply;
    newReply = 0;

    data = reply->friendList();
    qSort(data.begin(), data.end(), nameSortLesser);
    q->beginInsertRows(QModelIndex(), 0, data.count() - 1);
    emit q->countChanged();
    q->endInsertRows();
}

void FriendListModelPrivate::slotFailed()
{
    qDebug() << newReply->error();
    newReply->deleteLater();
    newReply = 0;
}

////// End of private class //////

FriendListModel::FriendListModel(QObject *parent):
    QAbstractListModel(parent), d_ptr(new FriendListModelPrivate(this))
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    setRoleNames(roles);
#endif
}

FriendListModel::~FriendListModel()
{
}

int FriendListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const FriendListModel);
    return d->data.count();
}

int FriendListModel::count() const
{
    return rowCount();
}

QueryManager * FriendListModel::queryManager() const
{
    Q_D(const FriendListModel);
    return d->queryManager;
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

void FriendListModel::setQueryManager(QueryManager *queryManager)
{
    Q_D(FriendListModel);
    if (d->queryManager != queryManager) {
        d->queryManager = queryManager;
        emit queryManagerChanged();
    }
}

void FriendListModel::request(const QString &graph)
{
    Q_D(FriendListModel);
    if (!d->queryManager) {
        return;
    }
    if (d->newReply) {
        return;
    }

    d->newReply = d->queryManager->queryFriendList(graph);
    connect(d->newReply, SIGNAL(finished()), this, SLOT(slotFinished()));
    connect(d->newReply, SIGNAL(failed()), this, SLOT(slotFailed()));
}

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
QHash<int, QByteArray> FriendListModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}
#endif

}

#include "moc_friendlistmodel.cpp"
