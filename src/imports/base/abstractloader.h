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

#include <QtCore/QObject>

namespace QFB
{

class QueryManager;
class AbstractReply;
class AbstractLoaderPrivate;
class AbstractLoader : public QObject
{
    Q_OBJECT
    /**
     * @short Query manager
     */
    Q_PROPERTY(QFB::QueryManager * queryManager READ queryManager WRITE setQueryManager
               NOTIFY queryManagerChanged)
public:
    virtual ~AbstractLoader();
    /**
     * @brief Query manager
     * @return query manager.
     */
    QueryManager * queryManager() const;
public Q_SLOTS:
    /**
     * @brief Set the query manager
     * @param queryManager query manager to set.
     */
    void setQueryManager(QueryManager *queryManager);
    /**
     * @brief Perform a request
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     */
    void request(const QString &graph, const QString &arguments = QString());
Q_SIGNALS:
    /**
     * @brief Query manager changed
     */
    void queryManagerChanged();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd d-pointer.
     * @param parent parent object.
     */
    explicit AbstractLoader(AbstractLoaderPrivate &dd, QObject *parent = 0);
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
    virtual AbstractReply * createReply(const QString &graph,
                                        const QString &arguments = QString()) = 0;
    /**
     * @short D-pointer
     */
    const QScopedPointer<AbstractLoaderPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractLoader)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotFailed())
    /// @endcond
};

}

#endif // QFB_ABSTRACTLOADER_H
