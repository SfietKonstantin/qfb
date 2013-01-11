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

#ifndef QFB_ABSTRACTPAGINGPROCESSOR_H
#define QFB_ABSTRACTPAGINGPROCESSOR_H

#include "abstractgraphprocessor.h"
#include <QtCore/QUrl>

namespace QFB
{

class AbstractPagingProcessorPrivate;
class QFBBASE_EXPORT AbstractPagingProcessor: public AbstractGraphProcessor
{
    Q_OBJECT
public:
    explicit AbstractPagingProcessor(QObject *parent = 0);
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
    explicit AbstractPagingProcessor(AbstractPagingProcessorPrivate &dd, QObject *parent = 0);
    /**
     * @brief Set the url used to get the next page
     * @param url url used to get the next page.
     */
    void setNextPageUrl(const QUrl &url);
private:
    Q_DECLARE_PRIVATE(AbstractPagingProcessor)
};

}

#endif // QFB_ABSTRACTPAGINGPROCESSOR_H
