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

#ifndef QFB_ABSTRACTGRAPHREPLY_H
#define QFB_ABSTRACTGRAPHREPLY_H

/**
 * @file abstractgraphreply.h
 * @brief Definition of QFB::AbstractGraphReply
 */

#include "abstractreply.h"
#include <QtCore/QPair>

class QIODevice;
class QNetworkAccessManager;
class QUrl;
namespace QFB
{

/**
 * @brief Arguments as a key-value pair
 */
typedef QPair<QString, QString> ArgumentPair;
class AbstractGraphReplyPrivate;
/**
 * @brief Base for a reply from Facebook
 *
 * This class contains base methods that are used for managing
 * a query to Facebook and getting the reply. It do not contain
 * any way to get the result. As with QFB::AbstractReply,
 * processData() should be implemented in order to parse the data
 * that is retrived from Facebook.
 *
 * @see AbstractReply
 *
 * @todo implement a way to manage OAuth exceptions.
 */
class QFBBASE_EXPORT AbstractGraphReply : public AbstractReply
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit AbstractGraphReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractGraphReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
public Q_SLOTS:
    /**
     * @brief Perform a request
     *
     * The request should be perform by sending a graph, like "me/friends",
     * the access token, and a list of arguments, formatted with the following
     * format: "key1=value1,key2=value2"
     *
     * @param graph graph entry of the Facebook graph API.
     * @param token access token.
     * @param arguments arguments.
     */
    void request(const QString &graph, const QString &token, const QString &arguments = QString());
protected:
    /**
     * @brief D-pointer constructor
     * @param dd D-pointer.
     * @param parent parent object.
     */
    explicit AbstractGraphReply(AbstractGraphReplyPrivate &dd, QObject *parent = 0);
    /**
     * @brief Process arguments
     *
     * This method can be used to process arguments before sending them
     * to the request. It makes them cleaner and can be used if arguments
     * needs to be precise, or if arguments are used for storage.
     *
     * @param arguments arguments to process.
     * @return processed arguments.
     */
    virtual QList<ArgumentPair> processArguments(const QList<ArgumentPair> &arguments);
    /**
     * @brief Graph
     * @return graph.
     */
    QString graph() const;
    /**
     * @brief Arguments
     * @return arguments.
     */
    QList<ArgumentPair> arguments() const;
private:
    Q_DECLARE_PRIVATE(AbstractGraphReply)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotError(QNetworkReply::NetworkError))
    /// @endcond
};

}

#endif // QFB_ABSTRACTGRAPHREPLY_H
