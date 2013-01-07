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

class QUrl;
class QNetworkAccessManager;
namespace QFB
{

class AbstractReplyPrivate;
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
public Q_SLOTS:
    /**
     * @brief Set error
     * @param error error to set.
     */
    void setError(const QString &error);
    void setFinished(bool ok);
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
