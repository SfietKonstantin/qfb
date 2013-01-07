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

#ifndef QFB_HELPER_P_H
#define QFB_HELPER_P_H

// Warning
//
// This file exists for the convenience
// of other qfb classes.
// This header file may change from version
// to version without notice or even be removed.

/**
 * @internal
 * @file helper_p.h
 * @short Global helper methods functions
 */

#include <QtCore/QPair>
#include <QtCore/QStringList>
#include <QtCore/QUrl>
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QtCore/QUrlQuery>
#endif

namespace QFB
{

typedef QPair<QString, QString> ArgumentPair;
/**
 * @internal
 * @brief FB_GRAPH_QUERY_URL
 *
 * Used by graphUrl()
 */
static const char *FB_GRAPH_QUERY_URL = "https://graph.facebook.com/";
/**
 * @internal
 * @brief FB_GRAPH_QUERY_TOKEN_KEY
 *
 * Used by graphUrl()
 */
static const char *FB_GRAPH_QUERY_TOKEN_KEY = "access_token";

inline QList<ArgumentPair> createArguments(const QString &arguments)
{
    QStringList argumentList = arguments.split(",");
    QList<ArgumentPair> trueArguments;
    foreach (QString argument, argumentList) {
        QStringList argumentEntriesList = argument.split("=");
        if (argumentEntriesList.count() == 2) {
            ArgumentPair argumentPair;
            argumentPair.first = argumentEntriesList.at(0).trimmed();
            argumentPair.second = argumentEntriesList.at(1).trimmed();
            trueArguments.append(argumentPair);
        }
    }
    return trueArguments;
}

/**
 * @internal
 * @brief Create a Facebook graph URL
 * @param graph graph.
 * @param token access token.
 * @param arguments other arguments.
 * @return An url pointing to the Facebook graph API.
 */
inline QUrl graphUrl(const QString &graph, const QString &token,
                     const QList<ArgumentPair> &arguments)
{
    QString urlString = QString(FB_GRAPH_QUERY_URL);
    urlString.append(graph);
    QUrl url (urlString);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    url.addQueryItem(FB_GRAPH_QUERY_TOKEN_KEY, token);
    foreach (ArgumentPair argumentPair, arguments) {
        url.addQueryItem(argumentPair.first, argumentPair.second);
    }

#else
    QUrlQuery urlQuery;
    urlQuery.addQueryItem(FB_GRAPH_QUERY_TOKEN_KEY, token);
    foreach (ArgumentPair argumentPair, arguments) {
        urlQuery.addQueryItem(argumentPair.first, argumentPair.second);
    }
    url.setQuery(urlQuery);
#endif
    return url;
}

/**
 * @internal
 * @brief Parse an URL from a string
 * @param urlString the URL as a string.
 * @return the parsed URL.
 */
inline QUrl parseUrl(const QString &urlString)
{
    return QUrl::fromPercentEncoding(urlString.toLocal8Bit());
}

}

#endif // QFB_HELPER_P_H
