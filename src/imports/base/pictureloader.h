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

#ifndef QFB_PICTURELOADER_H
#define QFB_PICTURELOADER_H

#include <QtCore/QObject>

namespace QFB
{
class QueryManager;
class PictureLoaderPrivate;
class PictureLoader : public QObject
{
    Q_OBJECT
    Q_ENUMS(Type)
    Q_PROPERTY(QFB::QueryManager * queryManager READ queryManager WRITE setQueryManager
               NOTIFY queryManagerChanged)
    Q_PROPERTY(Type type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString picturePath READ picturePath NOTIFY picturePathChanged)
public:
    enum Type {
        Square,
        Small,
        Normal,
        Large
    };
    explicit PictureLoader(QObject *parent = 0);
    virtual ~PictureLoader();
    QueryManager * queryManager() const;
    Type type() const;
    QString picturePath() const;
public Q_SLOTS:
    void setQueryManager(QueryManager *queryManager);
    void setType(Type type);
    void request(const QString &graph);
Q_SIGNALS:
    void queryManagerChanged();
    void typeChanged();
    void picturePathChanged();
protected:
    QScopedPointer<PictureLoaderPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(PictureLoader)
    /// @cond buggy-doxygen
    Q_PRIVATE_SLOT(d_func(), void slotFinished())
    Q_PRIVATE_SLOT(d_func(), void slotFailed())
    /// @endcond
};

}

#endif // QFB_PICTURELOADER_H
