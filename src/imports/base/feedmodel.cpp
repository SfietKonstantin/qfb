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
#include "abstractloadablemodel_p.h"

#include <QtCore/QDebug>

#include "querymanager.h"
#include "post.h"
#include "feedreply.h"
#include "postvalidator.h"

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
     * @brief Implementation of AbstractLoadableModelPrivate::processReply()
     * @param reply reply to be processed.
     * @return if the process is successful.
     */
    bool processReply(const AbstractGraphPagingReply *reply);
    void clear();
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

bool FeedModelPrivate::processReply(const AbstractGraphPagingReply *reply)
{
    Q_Q(FeedModel);
    const FeedReply *feedReply = qobject_cast<const FeedReply *>(reply);
    if (!feedReply) {
        return false;
    }

    QList<Post *> feed = feedReply->feed();
    QList<Post *> finalFeed;
    foreach (Post *post, feed) {
        bool postOk = true;
        if (validator) {
            if (!validator->validate(post)) {
                postOk = false;
            }
        }

        if (!postOk) {
            post->deleteLater();
        } else {
            post->setParent(q);
            finalFeed.append(post);
        }
    }

    if (feed.isEmpty()) {
        setDoNotHaveNext();
        return true;
    }

    q->beginInsertRows(QModelIndex(), data.count(), data.count() + finalFeed.count() - 1);
    data.append(finalFeed);
    emit q->countChanged();
    q->endInsertRows();
    return true;
}

void FeedModelPrivate::clear()
{
    Q_Q(FeedModel);
    // Clean old data
    if (!data.isEmpty()) {
        q->beginRemoveRows(QModelIndex(), 0, q->rowCount() - 1);
        qDeleteAll(data);
        data.clear();
        q->endRemoveRows();
    }
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

AbstractGraphPagingReply * FeedModel::createReply(const QString &graph, const QString &arguments)
{
//    return queryManager()->queryFeed(graph, arguments);
    return 0;
}

QHash<int, QByteArray> FeedModel::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}
