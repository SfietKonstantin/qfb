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

#include "preprocessordata.h"
#include <QtCore/QStringList>

namespace QFB
{

/**
 * @internal
 * @brief Create arguments
 * @param arguments arguments as a string.
 * @return arguments as a list of argument pair.
 */
inline QList<ArgumentPair> createArguments(const QString &arguments)
{
    QStringList argumentList = arguments.split(",");
    QList<ArgumentPair> trueArguments;
    foreach (QString argument, argumentList) {
        int indexOfEqual = argument.indexOf("=");

        ArgumentPair argumentPair;
        argumentPair.first = argument.left(indexOfEqual);
        argumentPair.second = argument.right(argument.size() - indexOfEqual - 1);
        if (!argumentPair.first.isEmpty() && !argumentPair.second.isEmpty()) {
            trueArguments.append(argumentPair);
        }
    }
    return trueArguments;
}

PreprocessorData::PreprocessorData():
    d_ptr(new PreprocessorDataPrivate)
{
    setOperation(InvalidOperation);
}

PreprocessorData::PreprocessorData(const PreprocessorData &other):
    d_ptr(other.d_ptr)
{
}

PreprocessorData::~PreprocessorData()
{
}

QVariant & PreprocessorData::operator [](const QString &key)
{
    Q_D(PreprocessorData);
    return d->data[key];
}

QVariant PreprocessorData::operator [](const QString &key) const
{
    Q_D(const PreprocessorData);
    return d->data.value(key);
}

OperationType PreprocessorData::operation() const
{
    Q_D(const PreprocessorData);
    return d->operation;
}

QUrl PreprocessorData::url() const
{
    Q_D(const PreprocessorData);
    return d->url;
}

QString PreprocessorData::graph() const
{
    Q_D(const PreprocessorData);
    return d->graph;
}

QList<ArgumentPair> PreprocessorData::arguments() const
{
    Q_D(const PreprocessorData);
    return d->arguments;
}

QByteArray PreprocessorData::postData() const
{
    Q_D(const PreprocessorData);
    return d->postData;
}

QVariantMap PreprocessorData::data() const
{
    Q_D(const PreprocessorData);
    return d->data;
}

void PreprocessorData::setOperation(OperationType operationType)
{
    Q_D(PreprocessorData);
    d->operation = operationType;
}

void PreprocessorData::setUrl(const QUrl &url)
{
    Q_D(PreprocessorData);
    d->url = url;
}

void PreprocessorData::setGraph(const QString &graph)
{
    Q_D(PreprocessorData);
    d->graph = graph;
}

void PreprocessorData::setArguments(const QString &arguments)
{
    setArguments(createArguments(arguments));
}

void PreprocessorData::setArguments(const QList<ArgumentPair> &arguments)
{
    Q_D(PreprocessorData);
    d->arguments = arguments;
}

void PreprocessorData::setPostData(const QByteArray &postData)
{
    Q_D(PreprocessorData);
    d->postData = postData;
}
void PreprocessorData::setData(const QVariantMap &data)
{
    Q_D(PreprocessorData);
    d->data = data;
}

}
