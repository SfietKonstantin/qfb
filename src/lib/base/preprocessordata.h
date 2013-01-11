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

#ifndef QFB_PREPROCESSORDATA_H
#define QFB_PREPROCESSORDATA_H

#include "base_global.h"
#include <QtCore/QExplicitlySharedDataPointer>
#include <QtCore/QSharedData>
#include <QtCore/QUrl>
#include <QtCore/QVariantMap>
#include "qfb.h"
#include "argumentpair.h"

namespace QFB
{

struct PreprocessorDataPrivate: public QSharedData
{
    OperationType operation;
    QUrl url;
    QString graph;
    QList<ArgumentPair> arguments;
    QByteArray postData;
    QVariantMap data;
};


class QFBBASE_EXPORT PreprocessorData
{
public:
    explicit PreprocessorData();
    PreprocessorData(const PreprocessorData &other);
    virtual ~PreprocessorData();
    QVariant & operator[](const QString &key);
    QVariant operator[](const QString &key) const;
    OperationType operation() const;
    QUrl url() const;
    QString graph() const;
    QList<ArgumentPair> arguments() const;
    QByteArray postData() const;
    QVariantMap data() const;
    void setOperation(OperationType operationType);
    void setUrl(const QUrl &url);
    void setGraph(const QString &graph);
    void setArguments(const QString &arguments);
    void setArguments(const QList<ArgumentPair> &arguments);
    void setPostData(const QByteArray &postData);
    void setData(const QVariantMap &data);
private:
    QExplicitlySharedDataPointer<PreprocessorDataPrivate> d_ptr;
    Q_DECLARE_PRIVATE(PreprocessorData)
};

}

#endif // QFB_PREPROCESSORDATA_H
