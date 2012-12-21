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

#ifndef QFB_FEEDREPLY_H
#define QFB_FEEDREPLY_H

/**
 * @file feedreply.h
 * @brief Definition of QFB::FeedReply
 */

#include "abstractgraphreply.h"

namespace QFB
{

class Post;
class FeedReplyPrivate;
/**
 * @brief Reply containing a feed
 *
 * This class subclasses AbstractGraphReply, making it be able to parse
 * feeds. This reply, when finished, will create a list of posts
 * that have this reply as parent.
 *
 * @todo Allow the posts not to have this reply as parent.
 */
class QFBBASE_EXPORT FeedReply : public AbstractGraphReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit FeedReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit FeedReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    /**
     * @brief Feed
     * @return feed.
     */
    QList<Post *> feed() const;
    /**
     * @brief Implementation of AbstractReply::processData()
     * @param dataSource data source.
     * @return if the process is successful.
     */
    bool processData(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(FeedReply)
};

}

#endif // QFB_FEEDREPLY_H
