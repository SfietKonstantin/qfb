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

#ifndef QFB_ABSTRACTGRAPHPAGINGREPLY_H
#define QFB_ABSTRACTGRAPHPAGINGREPLY_H

/**
 * @file abstractgraphpagingreply.h
 * @brief Definition of QFB::AbstractGraphPagingReply
 */

#include "abstractgraphreply.h"

namespace QFB
{
class AbstractGraphPagingReplyPrivate;
/**
 * @brief Base class for a reply that have several pages
 *
 * This class is the base class for graph based replies that
 * have pages. It only provides some getters and setters, in
 * order for the implemented reply to set the next pages.
 *
 * setNextPageUrl() should be used in order to automatically
 * extract the relevant part of the URL that can be used in
 * a query for the next page.
 */
class QFBBASE_EXPORT AbstractGraphPagingReply: public AbstractGraphReply
{
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit AbstractGraphPagingReply(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param networkAccessManager network access manager.
     * @param parent parent object.
     */
    explicit AbstractGraphPagingReply(QNetworkAccessManager *networkAccessManager,
                                         QObject *parent = 0);
    /**
     * @brief Graph used to get the next page
     * @return graph used to get the next page.
     */
    QString nextPageGraph() const;
    /**
     * @brief Arguments used to get the next page
     * @return arguments used to get the next page.
     */
    QString nextPageArguments() const;
protected:
    /**
     * @brief D-pointer constructor
     * @param dd D-pointer.
     * @param parent parent object.
     */
    explicit AbstractGraphPagingReply(AbstractGraphReplyPrivate &dd, QObject *parent = 0);
    /**
     * @brief Set the url used to get the next page
     * @param url url used to get the next page.
     */
    void setNextPageUrl(const QUrl &url);
private:
    Q_DECLARE_PRIVATE(AbstractGraphPagingReply)
};

}

#endif // QFB_ABSTRACTGRAPHPAGINGREPLY_H
