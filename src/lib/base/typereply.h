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

#ifndef QFB_TYPEREPLY_H
#define QFB_TYPEREPLY_H

#include "abstractgraphreply.h"
#include "object.h"

namespace QFB
{

class TypeReplyPrivate;
class QFBBASE_EXPORT TypeReply : public AbstractGraphReply
{
    Q_OBJECT
public:
    explicit TypeReply(QObject *parent = 0);
    explicit TypeReply(QNetworkAccessManager *networkAccessManager, QObject *parent = 0);
    Object * object() const;
protected:
    QList<ArgumentPair> processArguments(const QList<ArgumentPair> &arguments);
    /**
     * @brief Implementation of AbstractReply::processData()
     * @param dataSource data source.
     * @return if the process is successful.
     */
    bool processData(QIODevice *dataSource);
private:
    Q_DECLARE_PRIVATE(TypeReply)
};

}

#endif // TYPEREPLY_H
