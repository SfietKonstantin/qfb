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

#ifndef QFB_REQUEST_H
#define QFB_REQUEST_H

#include "base_global.h"
#include <QtCore/QMetaType>
#include <QtCore/QSharedData>
#include <QtCore/QExplicitlySharedDataPointer>
#include "qfb.h"

namespace QFB
{

struct RequestPrivate: public QSharedData
{
    int id;
    RequestType type;
};

class QFBBASE_EXPORT Request
{
public:
    explicit Request();
    explicit Request(int id, RequestType type);
    Request(const Request &other);
    virtual ~Request();
    bool operator==(const Request &other) const;
    bool operator!=(const Request &other) const;
    bool isValid() const;
    int id() const;
    RequestType type() const;
    void setId(int id);
    void setType(RequestType type);
private:
    QExplicitlySharedDataPointer<RequestPrivate> d_ptr;
    Q_DECLARE_PRIVATE(Request)
};

}

Q_DECLARE_METATYPE(QFB::Request)

#endif // QFB_REQUEST_H
