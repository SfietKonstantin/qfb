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

#ifndef QFB_POSTLOADER_H
#define QFB_POSTLOADER_H

/**
 * @file postloader.h
 * @brief Definition of QFB::PostLoader
 */

#include "abstractgraphloader.h"

namespace QFB
{

class Post;
class PostLoaderPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT PostLoader: public AbstractGraphLoader
{
    Q_OBJECT
    /**
     * @brief Post
     */
    Q_PROPERTY(QFB::Post * post READ post NOTIFY postChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit PostLoader(QObject *parent = 0);
    /**
     * @brief Post
     * @return post.
     */
    Post * post() const;
Q_SIGNALS:
    /**
     * @brief Post changed
     */
    void postChanged();
protected:
    /**
     * @brief Implementation of AbstractGraphLoader::createRequest()
     * @param graph Graph.
     * @param arguments Arguments.
     * @return Created request.
     */
     Request createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Implementation of AbstractLoader::handleReply()
     * @param processor Processor to handle.
     */
     void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(PostLoader)
};

}

#endif // QFB_POSTLOADER_H
