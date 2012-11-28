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

#ifndef QFB_ABSTRACTREPLY_H
#define QFB_ABSTRACTREPLY_H

/**
 * @file abstractreply.h
 * @brief Definition of QFB::AbstractReply
 */

#include "base_global.h"
#include <QtCore/QObject>
#include <QtCore/QMetaType>

class QIODevice;
class QNetworkAccessManager;
class QUrl;
namespace QFB
{

class AbstractReplyPrivate;
/**
 * @brief Base for a reply from Facebook
 *
 * This class contains base methods that are used for managing
 * a query to Facebook and getting the reply. It do not contain
 * any way to get the result, and only provides a pure virtual
 * method, processData(), that should be implemented in order to
 * parse the data that is provided by Facebook.
 *
 * Retrived data can be stored in a subclass of this class, and
 * returned through a specific getter. Signals that informs that
 * data is ready do not need to be emitted, as they are emitted
 * automatically.
 *
 * Note that these replies objects only stores one reply. In order
 * to perform another request, you must create a new one.
 *
 * Warning: deleting this class should be done manually as, by
 * default, it stays in memory.
 *
 * @todo implement a way to manage OAuth exceptions.
 */
class QFBBASE_EXPORT AbstractReply : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit AbstractReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    /**
     * @brief Destructor
     */
    virtual ~AbstractReply();
public Q_SLOTS:
    /**
     * @brief Perform a request
     * @param graph graph entry of the Facebook graph API.
     * @param token access token.
     */
    void request(const QString &graph, const QString &token);
Q_SIGNALS:
    /**
     * @brief Error
     *
     * This signal is emitted when the loading failed, or when
     * the returned data is not correct.
     */
    void error();
    /**
     * @brief Finished
     *
     * This signal is emitted when the loading is a success.
     */
    void finished();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd D-pointer.
     * @param parent parent object.
     */
    explicit AbstractReply(AbstractReplyPrivate &dd, QObject *parent = 0);
    /**
     * @brief Process data
     *
     * This method should be implemented in order to process the
     * data that is retrived from Facebook.
     *
     * @param dataSource data source.
     * @return if the process is successful.
     */
    virtual bool processData(QIODevice *dataSource) = 0;
    /**
     * @brief D-pointer
     */
    QScopedPointer<AbstractReplyPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(AbstractReply)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotError(QNetworkReply::NetworkError))
    /// @endcond
};

}

Q_DECLARE_METATYPE(QFB::AbstractReply *)

#endif // QFB_ABSTRACTREPLY_H
