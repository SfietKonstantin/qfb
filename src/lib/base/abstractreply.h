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
#include <QtCore/QThread>

class QIODevice;
class QUrl;
class QNetworkAccessManager;
namespace QFB
{

class AbstractReplyPrivate;

/**
 * @brief Base for a reply
 *
 * This class contains base methods that are used for managing
 * a network query and getting the reply. It do not contain
 * any way to get the result, and only provides a pure virtual
 * method, processData(), that should be implemented in order to
 * parse the retrived data.
 *
 * Retrived data can be stored in a subclass of this class, and
 * returned through a specific getter. Signals that informs that
 * data is ready do not need to be emitted, as they are emitted
 * automatically.
 *
 * This class also provides preprocessRequest(), that can be used
 * to handle caching, and get(), that is the method that perform
 * the network operation.
 *
 * Note that these replies objects only stores one reply. In order
 * to perform another request, you must create a new one.
 *
 * Warning: deleting this class should be done manually as, by
 * default, it stays in memory.
 */
class QFBBASE_EXPORT AbstractReply : public QThread
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
    /**
     * @brief If the reply process is running
     * @return if the reply process is running.
     */
    bool isLoading() const;
    /**
     * @brief Error
     * @return error.
     */
    QString error() const;
Q_SIGNALS:
    /**
     * @brief Error
     *
     * This signal is emitted when the loading failed, or when
     * the returned data is not correct.
     */
    void loadingFailed();
    /**
     * @brief Finished
     *
     * This signal is emitted when the loading is a success.
     */
    void loadingFinished();
protected:
    /**
     * @brief D-pointer constructor
     * @param dd D-pointer.
     * @param parent parent object.
     */
    explicit AbstractReply(AbstractReplyPrivate &dd, QObject *parent = 0);
    /**
     * @internal
     * @brief Event management
     * @param event event.
     * @return if the event is managed.
     */
    bool event(QEvent *event);
    /**
     * @brief Preprocess request
     *
     * This method is used to do a preprocessing step before perfomring
     * the request. It can be used, for example, to check a cache, before
     * downloading resources.
     *
     * It should return false if the request should be performed, or true
     * if the request should not. If it returns true, a finished() signal
     * will be emitted.
     *
     * @return if the process should be performed.
     */
    virtual bool preprocesssRequest();
    /**
     * @brief Perform the network operation
     *
     * This method is used to perform the network operation, by passing
     * the URL that is used for that operation. Network operations are
     * done through GET.
     *
     * @param url URL to use for the network operation.
     */
    void get(const QUrl &url);
    /**
     * @brief Url
     * @return url.
     */
    QUrl url() const;
    /**
     * @brief Process data
     *
     * This method should be implemented in order to process the
     * data that is retrived.
     *
     * @param dataSource data source.
     * @return if the process is successful.
     */
    virtual bool processData(QIODevice *dataSource) = 0;
    /**
     * @brief Set error
     * @param error error to set.
     */
    void setError(const QString &error);
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

#endif // QFB_ABSTRACTREPLY_H
