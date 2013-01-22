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

/**
 * @brief Preprocessed data
 *
 * This class is used to store the data that should
 * be preprocessed. It contains a lot of properties,
 * that might not be used all the time.
 *
 * The url() property is used to store the URL of
 * the query. It can be preprocessed, and can be
 * changed in order to handle redirections.
 *
 * The operation() property is used to contain the
 * operation that is being carried out. It is used
 * internally, and should not be changed.
 *
 * graph() and arguments() are used to contain
 * the Facebook graph and arguments that are used
 * to perform a call through Facebook graph API.
 * Typically, they can be changed during a
 * preprocessing task.
 *
 * data() and postData() are used for the data
 * preprocessing. While data() contains the
 * data to be sent as a variant map, before
 * preprocessing, postData() contains the data to
 * be sent after preprocessing. This can be useful
 * if, for example, as a data to be preprocessed is
 * passed the path to an image, and the preprocessor
 * opens the image and serializes it.
 */
class QFBBASE_EXPORT PreprocessorData
{
public:
    /**
     * @brief Default constructor
     */
    explicit PreprocessorData();
    /**
     * @brief Copy constructor
     * @param other other preprocessor data.
     */
    PreprocessorData(const PreprocessorData &other);
    /**
     * @brief Destructor
     */
    virtual ~PreprocessorData();
    QVariant & operator[](const QString &key);
    QVariant operator[](const QString &key) const;
    OperationType operation() const;
    QUrl url() const;
    QString graph() const;
    QList<ArgumentPair> arguments() const;
    QVariantMap data() const;
    QByteArray postData() const;
    void setOperation(OperationType operationType);
    void setUrl(const QUrl &url);
    void setGraph(const QString &graph);
    void setArguments(const QString &arguments);
    void setArguments(const QList<ArgumentPair> &arguments);
    void setData(const QVariantMap &data);
    void setPostData(const QByteArray &postData);
private:
    QExplicitlySharedDataPointer<PreprocessorDataPrivate> d_ptr;
    Q_DECLARE_PRIVATE(PreprocessorData)
};

}

#endif // QFB_PREPROCESSORDATA_H
