#!/usr/bin/python
#
# This tool is used to quickly create models
# that are used to expose list of Facebook
# objects to a QML context
#
import argparse
import string
import re
import qfbtools

copyright = """/****************************************************************************************
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
"""

def generate(className, loadedClass):
    createHeader(className, loadedClass)
    createSource(className, loadedClass)

def createHeader(className, loadedClass):
    header = copyright

    header += """

#ifndef QFB_"""  + className.upper() + """_H
#define QFB_"""  + className.upper() + """_H

/**
 * @file """ + className.lower() + """.h
 * @brief Definition of QFB::""" + className + """
 */

#include "abstractloadablemodel.h"

namespace QFB
{

class QueryManager;
class """ + className + """Private;

/**
 * @short WRITE DOCUMENTATION HERE
 */
class QFBBASEIMPORT_EXPORT """ + className + """: public AbstractLoadableModel
{
    Q_OBJECT
public:
    /**
     * @short Model roles
     */
    enum """ + className + """Role {
        /**
        * @short Data role
        */
        DataRole = Qt::UserRole + 1
    };
    /**
     * @brief Default constructor
     * @param parent parent object.
     */
    explicit """ + className + """(QObject *parent = 0);
    /**
     * @short Reimplementation of rowCount
     *
     * @param parent parent model index.
     * @return number of rows in this model.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @short Reimplementation of data
     *
     * @param index model index where retrieve the data.
     * @param role role to retrieve.
     * @return retrieved data as a variant.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
protected:
    /**
     * @brief Implementation of AbstractLoadableModel::clear()
     */
    void clear();
    /**
     * @brief Reimplementation of AbstractLoadableModel::createRequest()
     * @param graph Graph.
     * @param arguments Arguments.
     * @return Created request.
     */
    Request createRequest(const QString &graph, const QString &arguments);
    /**
     * @brief Implementation of AbstractLoadableModel::handleReply()
     * @param processor Processor to handle.
     */
    void handleReply(AbstractPagingProcessor *processor);
    /**
     * @brief Role names
     * @return role names.
     */
    QHash<int, QByteArray> roleNames() const;
private:
    Q_DECLARE_PRIVATE(""" + className + """)
};

}

#endif // """ + className.upper() + """_H
"""

    headerFile = open(className.lower() + ".h", "w")
    headerFile.write(header)
    headerFile.close()

def createSource(className, loadedClass):
    source = copyright

    source += """

/**
 * @file """ + className.lower() + """.cpp
 * @brief Implementation of QFB::""" + className + """
 */

#include \"""" + className.lower() + """.h\"
#include "private/abstractloadablemodel_p.h"
#include "querymanager.h"
#include \"processors/objectlistprocessor.h\"
#include \"objects/""" + loadedClass.lower() + """.h\"

namespace QFB
{
/**
 * @internal
 * @brief Private class for QFB::""" + className + """
 */
class """ + className + """Private: public AbstractLoadableModelPrivate
{
public:
    /**
     * @internal
     * @brief Default constructor
     * @param q Q-pointer
     */
    """ + className + """Private(""" + className + """ *q);
    /**
     * @internal
     * @brief Data
     */
    QList<""" + loadedClass + """ *> data;
};

""" + className + """Private::""" + className + """Private(""" + className + """ *q):
    AbstractLoadableModelPrivate(q)
{
}

////// End of private class //////

""" + className + """::""" + className + """(QObject *parent):
    AbstractLoadableModel(*(new """ + className + """Private(this)), parent)
{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    setRoleNames(roleNames());
#endif
}

int """ + className + """::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    Q_D(const """ + className + """);
    return d->data.count();
}

QVariant """ + className + """::data(const QModelIndex &index, int role) const
{
    Q_D(const """ + className + """);
    int row = index.row();
    if (row < 0 || row >= rowCount()) {
        return QVariant();
    }

    """ + loadedClass + """ *item = d->data.at(row);

    switch (role) {
    case DataRole:
        return QVariant::fromValue(item);
        break;
    default:
        return QVariant();
        break;
    }
}

Request """ + className + """::createRequest(const QString &graph, const QString &arguments)
{
    if (queryManager()) {
        return queryManager()->queryObjectList(Object::""" + loadedClass
    source += """Type, graph, arguments);
    }
    return Request();
}

void """ + className + """::clear()
{
    Q_D(""" + className + """);
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    qDeleteAll(d->data);
    d->data.clear();
    emit countChanged();
    endRemoveRows();
}

void """ + className + """::handleReply(AbstractPagingProcessor *processor)
{
    Q_D(""" + className + """);
    ObjectListProcessor *objectListProcessor = qobject_cast<ObjectListProcessor *>(processor);
    if (!objectListProcessor) {
        return;
    }

    // TODO: adapt this code if needed
    QList<Object *> objectList = objectListProcessor->objectList();

    if (objectList.isEmpty()) {
        setDoNotHaveNext();
        return;
    }

    QList<""" + loadedClass + """*> castedObjectList;
    foreach (Object *object, objectList) {
        """ + loadedClass + """ *castedObject = qobject_cast<""" + loadedClass + """*>(object);
        if (castedObject) {
            castedObjectList.append(castedObject);
        }
    }

    beginInsertRows(QModelIndex(), d->data.count(), d->data.count() + castedObjectList.count() - 1);
    d->data.append(castedObjectList);
    emit countChanged();
    endInsertRows();
}

QHash<int, QByteArray> """ + className + """::roleNames() const
{
    QHash <int, QByteArray> roles;
    roles.insert(DataRole, "data");
    return roles;
}

}
"""


    sourceFile = open(className.lower() + ".cpp", "w")
    sourceFile.write(source)
    sourceFile.close()

# Main
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='QFB loader writer')
    parser.add_argument('className', metavar='className', type=str,
                        help="""Class name""")
    parser.add_argument('loadedClass', metavar='loadedClass', type=str,
                        help="""Loaded class""")
    args = parser.parse_args()

    className = args.className
    loadedClass = args.loadedClass
    generate(className, loadedClass)


