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

#ifndef QFB_ABSTRACTREPLY_P_H
#define QFB_ABSTRACTREPLY_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file abstractreply_p.h
 * @brief Definition of QFB::AbstractReplyPrivate
 */

#include <QtNetwork/QNetworkReply>

class QNetworkAccessManager;
namespace QFB
{
class AbstractReply;
class AbstractReplyPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    AbstractReplyPrivate(AbstractReply *q);
    /**
     * @internal
     * @brief Get the redirect URL
     *
     * This method is used to get the redirect URL that the current
     * reply provided. If the redirect URL is different, the reply
     * will load the given URL.
     *
     * @return redirect URL
     */
    QUrl redirectUrl();
    /**
     * @internal
     * @brief Slot used to react to finish
     */
    void slotFinished();
    /**
     * @internal
     * @brief Slot used to react to error
     * @param error error.
     */
    void slotError(QNetworkReply::NetworkError error);
    /**
     * @internal
     * @brief Network access manager
     */
    QNetworkAccessManager *networkAccessManager;
    /**
     * @internal
     * @brief Reply
     */
    QNetworkReply *reply;
    /**
     * @internal
     * @brief Url
     */
    QUrl url;
    /**
     * @internal
     * @brief If the reply is running
     */
    bool running;
    /**
     * @internal
     * @brief If the reply is an error
     */
    bool isError;
    /**
     * @internal
     * @brief Error message
     */
    QString error;
protected:
    /**
     * @internal
     * @brief Q-pointer
     */
    AbstractReply * const q_ptr;
private:
    Q_DECLARE_PUBLIC(AbstractReply)
};

}

#endif // QFB_ABSTRACTREPLY_P_H
