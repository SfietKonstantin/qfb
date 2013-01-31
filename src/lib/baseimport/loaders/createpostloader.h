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

#ifndef QFB_CREATEPOSTLOADER_H
#define QFB_CREATEPOSTLOADER_H

/**
 * @file createpostloader.h
 * @brief Definition of QFB::CreatePostLoader
 */

#include "abstractgraphpostloader.h"

namespace QFB
{

class Object;
class CreatePostLoaderPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT CreatePostLoader: public AbstractGraphPostLoader
{
    Q_OBJECT
    /**
     * @brief Object
     */
    Q_PROPERTY(QFB::Object * reply READ reply NOTIFY replyChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit CreatePostLoader(QObject *parent = 0);
    /**
     * @brief Reply
     * @return reply.
     */
    Object * reply() const;
    QString message() const;
public Q_SLOTS:
    void setMessage(const QString &message);
Q_SIGNALS:
    /**
     * @brief Reply changed
     */
    void replyChanged();
    void messageChanged();
protected:
    QVariantMap data() const;
    /**
     * @brief Implementation of AbstractGraphLoader::createRequest()
     * @param graph Graph.
     * @param arguments Arguments.
     * @return Created request.
     */
     Query createRequest(const QString &graph, const QVariantMap &data);
    /**
     * @brief Implementation of AbstractLoader::handleReply()
     * @param processor Processor to handle.
     */
     void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(CreatePostLoader)
};

}

#endif // QFB_CREATEPOSTLOADER_H
