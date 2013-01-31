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

#ifndef POSTHELPER_H
#define POSTHELPER_H

#include <QtCore/QObject>
#include "objects/post.h"

class PostHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QFB::Post * post READ post WRITE setPost NOTIFY postChanged)
    Q_PROPERTY(bool fancy READ fancy WRITE setFancy NOTIFY fancyChanged)
    Q_PROPERTY(QString toFacebookId READ toFacebookId WRITE setToFacebookId
               NOTIFY toFacebookIdChanged)
    Q_PROPERTY(QString header READ header NOTIFY headerChanged)
    Q_PROPERTY(QFB::NamedObject * to READ to NOTIFY toChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(QString via READ via NOTIFY viaChanged)
public:
    explicit PostHelper(QObject *parent = 0);
    QFB::Post * post() const;
    bool fancy() const;
    QString toFacebookId() const;
    QString header() const;
    QFB::NamedObject * to() const;
    QString message() const;
    QString via() const;
public slots:
    void setPost(QFB::Post *post);
    void setFancy(bool fancy);
    void setToFacebookId(const QString &toFacebookId);
signals:
    void postChanged();
    void fancyChanged();
    void toFacebookIdChanged();
    void headerChanged();
    void toChanged();
    void messageChanged();
    void viaChanged();
private:
    void createPost();
    static QString elideText(const QString &text, int count);
    QFB::Post *m_post;
    bool m_fancy;
    QString m_toFacebookId;
    QString m_header;
    QFB::NamedObject *m_to;
    QString m_message;
    QString m_via;
};

#endif // POSTHELPER_H
