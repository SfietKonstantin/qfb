/****************************************************************************************
 * Copyright (C) 2011 Lucien XU <sfietkonstantin@free.fr>                               *
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

#ifndef QFB_BASE_PLUGIN_H
#define QFB_BASE_PLUGIN_H

/**
 * @file qml/base_plugin.h
 * @short Definition of QFB::BasePlugin (Qt5 version)
 */

#include <QtQml/QQmlExtensionPlugin>

namespace QFB
{
/**
 * @internal
 * @short Base QML plugin for qfb (Qt5 header)
 */
class BasePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    /**
     * @internal
     * @short Register types
     * @param uri uri used in the import.
     */
    virtual void registerTypes(const char *uri);
};

}

#endif // QFB_BASE_PLUGIN_H

