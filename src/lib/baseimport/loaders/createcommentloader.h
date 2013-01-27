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

#ifndef QFB_CREATECOMMENTLOADER_H
#define QFB_CREATECOMMENTLOADER_H

/**
 * @file createcommentloader.h
 * @brief Definition of QFB::CreateCommentLoader
 */

#include "abstractgraphloader.h"

namespace QFB
{

class Object;
class CreateCommentLoaderPrivate;
/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT CreateCommentLoader: public AbstractGraphLoader
{
    Q_OBJECT
    /**
     * @brief Object
     */
    Q_PROPERTY(QFB::Object * object READ object NOTIFY objectChanged)
    Q_PROPERTY(QString comment READ comment WRITE setComment NOTIFY commentChanged)
public:
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit CreateCommentLoader(QObject *parent = 0);
    /**
     * @brief Object
     * @return object.
     */
    Object * object() const;
    QString comment() const;
public Q_SLOTS:
    void setComment(const QString &comment);
Q_SIGNALS:
    /**
     * @brief Object changed
     */
    void objectChanged();
    void commentChanged();
protected:
    /**
     * @brief Implementation of AbstractGraphLoader::createRequest()
     * @param graph Graph.
     * @param arguments Arguments.
     * @return Created request.
     */
    Query createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Implementation of AbstractLoader::handleReply()
     * @param processor Processor to handle.
     */
     void handleReply(AbstractProcessor *processor);
private:
    Q_DECLARE_PRIVATE(CreateCommentLoader)
};

}

#endif // QFB_CREATECOMMENTLOADER_H
