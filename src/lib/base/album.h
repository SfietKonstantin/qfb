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

#ifndef QFB_ALBUM_H
#define QFB_ALBUM_H

#include "namedobject.h"
#include <QtCore/QDateTime>
#include <QtCore/QUrl>

namespace QFB
{

class QFBBASE_EXPORT Album: public NamedObject
{
    Q_OBJECT
    /**
     * @short The profile that created this album
     */
    Q_PROPERTY(QFB::NamedObject * from READ from CONSTANT)
    /**
     * @short The description of the album
     */
    Q_PROPERTY(QString description READ description CONSTANT)
    /**
     * @short The location of the album
     */
    Q_PROPERTY(QString location READ location CONSTANT)
    Q_PROPERTY(QUrl link READ link CONSTANT)
    Q_PROPERTY(QString coverPhoto READ coverPhoto CONSTANT)
    /// @todo privacy
    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(QString type READ type CONSTANT)
    /**
     * @short The time the photo album was initially created
     */
    Q_PROPERTY(QDateTime createdTime READ createdTime CONSTANT)
    /**
     * @short The last time the photo album was updated
     */
    Q_PROPERTY(QDateTime updatedTime READ updatedTime CONSTANT)
    Q_PROPERTY(bool canUpload READ canUpload CONSTANT)
public:
    explicit Album(QObject *parent = 0);
    explicit Album(const PropertiesMap propertiesMap, QObject *parent = 0);
    /**
     * @brief From
     * @return from.
     */
    NamedObject * from() const;
    QString description() const;
    QString location() const;
    QUrl link() const;
    QString coverPhoto() const;
    int count() const;
    QString type() const;
    QDateTime createdTime() const;
    QDateTime updatedTime() const;
    bool canUpload() const;
private:
    Q_DECLARE_PRIVATE(ObjectBase)
};

}

Q_DECLARE_METATYPE(QFB::Album *)

#endif // QFB_ALBUM_H
