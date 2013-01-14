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

#ifndef QFB_QUERYMANAGER_H
#define QFB_QUERYMANAGER_H

/**
 * @file querymanager.h
 * @brief Definition of QFB::QueryManager
 */

#include "base_global.h"
#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include "objects/object.h"

class QUrl;
class QNetworkAccessManager;
class QNetworkReply;
namespace QFB
{
class Request;
class AbstractProcessor;
class QueryManagerPrivate;

/**
 * @brief Query manager
 *
 * This class is the central class that manages queries to
 * Facebook, queues tasks and send notifications when the
 * tasks are finished.
 *
 * It first provides the token() property, that should
 * be the access token that is used by the application.
 * Nearly all requests to Facebook need that token to
 * be successful.
 *
 * @todo do not force the use of token
 * @todo get a better error management
 *
 * It then provides numorous methods that are used to get
 * an object, or a collection of objects from Facebook.
 * All these methods returns a Request object, that is
 * used for other classes to track the status of the
 * query.
 *
 * When a request is replied and terminated, the query
 * manager send notifications by broadcasting the signal
 * finished() or error(). These signals send the Request
 * as first argument, so classes concerned by a specific
 * request should compare the sent requests with the one
 * they got when performing the query.
 *
 * The finished() signal also provides the processor
 * that were used to parse the result. By casting the
 * processor to the specific one, the class is able to
 * retrieve the result that is hold by the processor.
 *
 * @section memoryManagement Memory management
 *
 * When a processor is returned through the finished()
 * signal, it is not deleted and stays in memory. The
 * class that is concerned by that reply should delete
 * the processor afterwards. When an error occurs, the
 * processor is deleted, since it is not useful anymore.
 *
 * @todo the name "query manager" do not fit with request
 *
 * @see AbstractProcessor
 */
class QFBBASE_EXPORT QueryManager : public QObject
{
    Q_OBJECT
    /**
     * @short Access token
     */
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit QueryManager(QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~QueryManager();
    /**
     * @brief Access token
     * @return access token.
     */
    QString token() const;
    /**
     * @brief Query an image
     * @param url url to the image.
     */
    Request queryImage(const QUrl &url);
    /**
     * @brief Query a picture
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     */
    Request queryPicture(const QString &graph, const QString &arguments = QString());
    Request queryType(const QString &graph, const QString &arguments = QString());
    /**
     * @brief Query an object
     * @param graph graph entry of the Facebook graph API.
     * @param arguments arguments.
     */
    Request queryObject(QFB::Object::ObjectType type, const QString &graph,
                        const QString &arguments = QString());
    Request queryObjectList(QFB::Object::ObjectType type, const QString &graph,
                            const QString &arguments = QString());
public Q_SLOTS:
    /**
     * @brief Set the access token
     * @param token access token to set.
     */
    void setToken(const QString &token);
signals:
    /**
     * @brief Access token changed
     */
    void tokenChanged();
    /**
     * @brief Error in a query
     * @param request concerned request.
     * @param errorString error message.
     */
    void error(const QFB::Request &request, const QString &errorString);
    /**
     * @brief A query is terminated
     *
     * This signal provides the processor that was used to get the reply
     * as an AbstractProcessor. In order to get the result, it should
     * be cast to the correct form.
     *
     * @param request concerned request.
     * @param processor processor used to process the reply.
     */
    void finished(const QFB::Request &request, AbstractProcessor *processor);
protected:
    /**
     * @brief D-pointer
     */
    QScopedPointer<QueryManagerPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(QueryManager)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotPreprocessFinished(bool needLoading))
    Q_PRIVATE_SLOT(d_func(), void slotPreprocessError())
    Q_PRIVATE_SLOT(d_func(),
                   void createPostprocessor(const QFB::Request &request, QIODevice *dataSource))
    Q_PRIVATE_SLOT(d_func(), void slotNetworkError(const QFB::Request &request))
    Q_PRIVATE_SLOT(d_func(), void slotPostprocessFinished())
    Q_PRIVATE_SLOT(d_func(), void slotPostprocessError())
    /// @endcond
};

}

#endif // QFB_QUERYMANAGER_H
