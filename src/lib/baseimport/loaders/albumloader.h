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

#ifndef QFB_ALBUMLOADER_H
#define QFB_ALBUMLOADER_H

/**
 * @file albumloader.h
 * @brief Definition of QFB::AlbumLoader
 */

#include "abstractgraphloader.h"

namespace QFB
{

class Album;
class AlbumLoaderPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT AlbumLoader: public AbstractGraphLoader
{
    Q_OBJECT
    /**
     * @brief Album
     */
    Q_PROPERTY(QFB::Album * album READ album NOTIFY albumChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit AlbumLoader(QObject *parent = 0);
    /**
     * @brief Album
     * @return album.
     */
    Album * album() const;
Q_SIGNALS:
    /**
     * @brief Album changed
     */
    void albumChanged();
protected:
    /**
     * @brief Implementation of AbstractGraphLoader::createRequest()
     * @param graph Graph.
     * @param arguments Arguments.
     * @return Created request.
     */
     Query createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Implementation of AbstractLoader::handleReply()
     * @param processor Processor to handle.
     */
     void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(AlbumLoader)
};

}

#endif // QFB_ALBUMLOADER_H
