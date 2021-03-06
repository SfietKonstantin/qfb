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
 * @file likelistmodel.cpp
 * @brief Implementation of QFB::LikeListModel
 */

#include "likelistmodel.h"
#include "private/abstractloadablemodel_p.h"
#include "querymanager.h"
#include "processors/objectlistprocessor.h"
#include "objects/namedobject.h"

namespace QFB
{
/**
 * @internal
 * @brief Private class for QFB::LikeListModel
 */
class LikeListModelPrivate: public AbstractLoadableModelPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    LikeListModelPrivate(LikeListModel *q);
    /**
     * @internal
     * @brief Data
     */
    QList<NamedObject *> data;
};

LikeListModelPrivate::LikeListModelPrivate(LikeListModel *q):
    AbstractLoadableModelPrivate(q)
{
}

////// End of private class //////

LikeListModel::LikeListModel(QObject *parent):
    AbstractLoadableModel(*(new LikeListModelPrivate(this)), parent)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    setRoleNames(roleNames());
#endif
}

int LikeListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const LikeListModel);
    return d->data.count();
}

QVariant LikeListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const LikeListModel);
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

bool LikeListModel::contains(const QString &facebookId) const
{
    Q_D(const LikeListModel);
    bool containUser = false;
    foreach (NamedObject *object, d->data) {
        if (object->facebookId() == facebookId) {
            containUser = true;
        }
    }
    return containUser;
}

Query LikeListModel::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObjectList(Object::UnknownType, graph, arguments);
    }
    return Query();
}

void LikeListModel::clear()
{
    Q_D(LikeListModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    qDeleteAll(d->data);
    d->data.clear();
    emit countChanged();
    endRemoveRows();
}

void LikeListModel::handleReply(AbstractPagingProcessor *processor, LoadMoreOperation operation)
{
    Q_D(LikeListModel);
    ObjectListProcessor *objectListProcessor = qobject_cast<ObjectListProcessor *>(processor);
    if (!objectListProcessor) {
        return;
    }

    // TODO: adapt this code if needed
    QList<Object *> objectList = objectListProcessor->objectList();

    if (objectList.isEmpty()) {
        setDoNotHaveMore();
        return;
    }

    QList<NamedObject*> castedObjectList;
    foreach (Object *object, objectList) {
        NamedObject *castedObject = qobject_cast<NamedObject*>(object);
        if (castedObject) {
            castedObjectList.append(castedObject);
        }
    }

    switch (operation) {
    case LoadPreviousOperation:
        beginInsertRows(QModelIndex(), 0, castedObjectList.count() - 1);
        castedObjectList.append(d->data);
        d->data = castedObjectList;
        break;
    default:
        beginInsertRows(QModelIndex(), d->data.count(),
                        d->data.count() + castedObjectList.count() - 1);
        d->data.append(castedObjectList);
        break;
    }
    emit countChanged();
    endInsertRows();
}

QHash<int, QByteArray> LikeListModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}
