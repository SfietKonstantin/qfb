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

#ifndef QFB_POST_H
#define QFB_POST_H

#include "base_global.h"
#include "object.h"

#include <QtCore/QDateTime>
#include <QtCore/QUrl>

namespace QFB
{

class UserBase;
class QFBBASE_EXPORT Post: public Object
{
    Q_OBJECT
    Q_PROPERTY(QFB::UserBase * from READ from CONSTANT)
    Q_PROPERTY(QVariantList to READ toVariant CONSTANT)
    Q_PROPERTY(QString message READ message CONSTANT)
    /// @todo message_tags
    /// @todo place
    Q_PROPERTY(QUrl picture READ picture CONSTANT)
    Q_PROPERTY(QUrl link READ link CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString caption READ caption CONSTANT)
    Q_PROPERTY(QString description READ description CONSTANT)
    Q_PROPERTY(QUrl source READ source CONSTANT)
    /// @todo properties
    Q_PROPERTY(QUrl icon READ icon CONSTANT)
    /// @todo actions
    /// @todo privacy
    /// @todo do a better type
    Q_PROPERTY(QString type READ type CONSTANT)
    /// @todo likes
    /// @todo place
    Q_PROPERTY(QString story READ story CONSTANT)
    /// @todo story_tags
    /// @todo with_tags
    /// @todo comments
    Q_PROPERTY(QString objectId READ objectId CONSTANT)
    /// @todo application
    Q_PROPERTY(QDateTime createdTime READ createdTime CONSTANT)
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    /// @todo include_hidden
public:
    /**
     * @brief Invalid constructor
     * @param parent parent object.
     */
    explicit Post(QObject *parent = 0);
    /**
     * @brief Default constructor
     * @param propertiesMap properties.
     * @param parent parent object.
     */
    explicit Post(const PropertiesMap propertiesMap, QObject *parent = 0);
    UserBase * from() const;
    QVariantList toVariant() const;
    QList<UserBase *> to() const;
    QString message() const;
    QUrl picture() const;
    QUrl link() const;
    QString name() const;
    QString caption() const;
    QString description() const;
    QUrl source() const;
    QUrl icon() const;
    QString type() const;
    QString story() const;
    QString objectId() const;
    QDateTime createdTime() const;
    QDateTime updatedTime() const;
private:
    Q_DECLARE_PRIVATE(Object)
};

}

Q_DECLARE_METATYPE(QFB::Post *)

#endif // QFB_POST_H
