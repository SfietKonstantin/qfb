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

#ifndef QFB_USERLOADER_H
#define QFB_USERLOADER_H

/**
 * @file userloader.h
 * @brief Definition of QFB::UserLoader
 */

#include "abstractgraphloader.h"

namespace QFB
{

class User;
class UserLoaderPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT UserLoader: public AbstractGraphLoader
{
    Q_OBJECT
    /**
     * @brief User
     */
    Q_PROPERTY(QFB::User * user READ user NOTIFY userChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit UserLoader(QObject *parent = 0);
    /**
     * @brief User
     * @return user.
     */
    User * user() const;
Q_SIGNALS:
    /**
     * @brief User changed
     */
    void userChanged();
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
    Q_DECLARE_PRIVATE(UserLoader)
};

}

#endif // QFB_USERLOADER_H
