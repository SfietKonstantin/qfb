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
 * @file photolistmodel.cpp
 * @brief Implementation of QFB::PhotoListModel
 */

#include "photolistmodel.h"
#include "private/abstractloadablemodel_p.h"
#include "querymanager.h"
#include "processors/objectlistprocessor.h"
#include "objects/photo.h"

namespace QFB
{
/**
 * @internal
 * @brief Private class for QFB::PhotoListModel
 */
class PhotoListModelPrivate: public AbstractLoadableModelPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    PhotoListModelPrivate(PhotoListModel *q);
    /**
     * @internal
     * @brief Data
     */
    QList<Photo *> data;
};

PhotoListModelPrivate::PhotoListModelPrivate(PhotoListModel *q):
    AbstractLoadableModelPrivate(q)
{
}

////// End of private class //////

PhotoListModel::PhotoListModel(QObject *parent):
    AbstractLoadableModel(*(new PhotoListModelPrivate(this)), parent)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    setRoleNames(roleNames());
#endif
}

int PhotoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const PhotoListModel);
    return d->data.count();
}

QVariant PhotoListModel::data(const QModelIndex &index, int role) const
{
    Q_D(const PhotoListModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    Photo *item = d->data.at(row);

    switch (role) {
    case DataRole:
        return QVariant::fromValue(item);
        break;
    default:
        return QVariant();
        break;
    }
}

Request PhotoListModel::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObjectList(Object::PhotoType, graph, arguments);
    }
    return Request();
}

void PhotoListModel::clear()
{
    Q_D(PhotoListModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    qDeleteAll(d->data);
    d->data.clear();
    emit countChanged();
    endRemoveRows();
}

void PhotoListModel::handleReply(AbstractPagingProcessor *processor)
{
    Q_D(PhotoListModel);
    ObjectListProcessor *objectListProcessor = qobject_cast<ObjectListProcessor *>(processor);
    if (!objectListProcessor) {
        return;
    }

    // TODO: adapt this code if needed
    QList<Object *> objectList = objectListProcessor->objectList();

    if (objectList.isEmpty()) {
        setDoNotHaveNext();
        return;
    }

    QList<Photo*> castedObjectList;
    foreach (Object *object, objectList) {
        Photo *castedObject = qobject_cast<Photo*>(object);
        if (castedObject) {
            castedObjectList.append(castedObject);
        }
    }

    beginInsertRows(QModelIndex(), d->data.count(), d->data.count() + castedObjectList.count() - 1);
    d->data.append(castedObjectList);
    emit countChanged();
    endInsertRows();
}

QHash<int, QByteArray> PhotoListModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}
