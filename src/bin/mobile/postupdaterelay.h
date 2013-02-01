/****************************************************************************************
 * Copyright (C) 2013 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef POSTUPDATERELAY_H
#define POSTUPDATERELAY_H

#include <QtCore/QObject>

class PostUpdateRelay : public QObject
{
    Q_OBJECT
public:
    explicit PostUpdateRelay(QObject *parent = 0);
signals:
    void updatePostLikesAndComments(const QString &postId, int likes, int comments);
public slots:
    void requestUpdatePostLikesAndComments(const QString &postId, int likes, int comments);
};

#endif // POSTUPDATERELAY_H
