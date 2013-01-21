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

#include "feedmodel.h"
#include "private/abstractloadablemodel_p.h"
#include <QtCore/QDebug>
#include "querymanager.h"
#include "postvalidator.h"
#include "processors/objectlistprocessor.h"
#include "objects/post.h"

namespace QFB
{

/**
 * @internal
 * @brief Private class for QFB::FeedModel
 */
class FeedModelPrivate: public AbstractLoadableModelPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    FeedModelPrivate(FeedModel *q);
    /**
     * @internal
     * @brief Data
     */
    QList<Post *> data;
    PostValidator *validator;
private:
    Q_DECLARE_PUBLIC(FeedModel)
};

FeedModelPrivate::FeedModelPrivate(FeedModel *q):
    AbstractLoadableModelPrivate(q)
{
    validator = 0;
}

////// End of private class //////

FeedModel::FeedModel(QObject *parent):
    AbstractLoadableModel(*(new FeedModelPrivate(this)), parent)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    setRoleNames(roleNames());
#endif
}

int FeedModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const FeedModel);
    return d->data.count();
}

QVariant FeedModel::data(const QModelIndex &index, int role) const
{
    Q_D(const FeedModel);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    Post *item = d->data.at(row);

    switch (role) {
    case DataRole:
        return QVariant::fromValue(item);
        break;
    default:
        return QVariant();
        break;
    }
}

PostValidator * FeedModel::validator() const
{
    Q_D(const FeedModel);
    return d->validator;
}

void FeedModel::setValidator(PostValidator *validator)
{
    Q_D(FeedModel);
    if (d->validator != validator) {
        d->validator = validator;
        emit validatorChanged();
    }
}

void FeedModel::handleReply(AbstractPagingProcessor *processor, LoadMoreOperation operation)
{
    Q_D(FeedModel);
    ObjectListProcessor *objectListProcessor = qobject_cast<ObjectListProcessor *>(processor);
    if (!objectListProcessor) {
        return;
    }

    QList<Object *> feed = objectListProcessor->objectList();

    QList<Post *> finalFeed;
    foreach (Object *post, feed) {
        Post *castedPost = qobject_cast<Post *>(post);
        bool postOk = castedPost;

        if (d->validator && postOk) {
            if (!d->validator->validate(castedPost)) {
                postOk = false;
            }
        }

        if (!postOk && castedPost) {
            castedPost->deleteLater();
        } else {
            castedPost->setParent(this);
            finalFeed.append(castedPost);
        }
    }

    if (feed.isEmpty()) {
        setDoNotHaveMore();
        return;
    }

    switch (operation) {
    case LoadPreviousOperation:
        beginInsertRows(QModelIndex(), 0, finalFeed.count() - 1);
        finalFeed.append(d->data);
        d->data = finalFeed;
        break;
    default:
        beginInsertRows(QModelIndex(), d->data.count(), d->data.count() + finalFeed.count() - 1);
        d->data.append(finalFeed);
        break;
    }
    emit countChanged();
    endInsertRows();
}

void FeedModel::clear()
{
    Q_D(FeedModel);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    qDeleteAll(d->data);
    d->data.clear();
    emit countChanged();
    endRemoveRows();
}

Request FeedModel::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObjectList(Object::PostType, graph, arguments);
    }
    return Request();
}

QHash<int, QByteArray> FeedModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}
