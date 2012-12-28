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
#include "post.h"

class PostHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QFB::Post * post READ post WRITE setPost NOTIFY postChanged)
    Q_PROPERTY(bool haveAdressee READ haveAdressee NOTIFY haveAdresseeChanged)
    Q_PROPERTY(QFB::NamedObject * to READ to NOTIFY toChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
public:
    explicit PostHelper(QObject *parent = 0);
    QFB::Post * post() const;
    bool haveAdressee() const;
    QFB::NamedObject * to() const;
    QString message() const;
public slots:
    void setPost(QFB::Post *post);
signals:
    void postChanged();
    void haveAdresseeChanged();
    void toChanged();
    void messageChanged();
private:
    void createPost();
    QFB::Post *m_post;
    bool m_haveAdressee;
    QFB::NamedObject *m_to;
    QString m_message;
};

#endif // POSTHELPER_H
