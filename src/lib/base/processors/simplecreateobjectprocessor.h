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

#ifndef QFB_SIMPLECREATEOBJECTPROCESSOR_H
#define QFB_SIMPLECREATEOBJECTPROCESSOR_H

#include "objectprocessor.h"

namespace QFB
{

class SimpleCreateObjectProcessor: public ObjectProcessor
{
    Q_OBJECT
public:
    explicit SimpleCreateObjectProcessor(QObject *parent = 0);
protected:
    QByteArray processPostData(const QVariantMap &data);
};

}

#endif // QFB_SIMPLECREATEOBJECTPROCESSOR_H
