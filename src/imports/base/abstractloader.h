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

#ifndef QFB_ABSTRACTLOADER_H
#define QFB_ABSTRACTLOADER_H

#include "loaderbase.h"

namespace QFB
{

class QueryManager;
class AbstractReply;
class LoaderBasePrivate;
class AbstractLoader : public LoaderBase
{
    Q_OBJECT
public Q_SLOTS:
    /**
     * @brief Perform a request
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     */
    void request(const QUrl &url);
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractLoader(LoaderBasePrivate &dd, QObject *parent = 0);
    virtual AbstractReply * createReply(const QUrl &url) = 0;
};

}

#endif // QFB_ABSTRACTLOADER_H
