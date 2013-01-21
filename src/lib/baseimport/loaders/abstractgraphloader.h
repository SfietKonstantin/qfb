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

#ifndef QFB_ABSTRACTGRAPHLOADER_H
#define QFB_ABSTRACTGRAPHLOADER_H

#include "abstractloader.h"

namespace QFB
{

class AbstractLoaderPrivate;
class QFBBASEIMPORT_EXPORT AbstractGraphLoader : public AbstractLoader
{
    Q_OBJECT
public:
    explicit AbstractGraphLoader(QObject *parent = 0);
public Q_SLOTS:
    /**
     * @brief Perform a request
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     */
    void request(const QString &graph, const QString &arguments = QString());
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractGraphLoader(AbstractLoaderPrivate &dd, QObject *parent = 0);
    /**
     * @brief Create a reply used in the request
     *
     * You can use the query manager to create replies you
     * are interested in.
     *
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     * @return a reply.
     */
    virtual Query createRequest(const QString &graph, const QString &arguments = QString()) = 0;
};

}

#endif // QFB_ABSTRACTGRAPHLOADER_H
