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

#ifndef QFB_DIALOGS_PLUGIN5_H
#define QFB_DIALOGS_PLUGIN5_H

/**
 * @internal
 * @file dialogs_plugin5.h
 * @short Definition of QFB::DialogsPlugin5 (Qt5)
 */

#include <QtQml/QQmlExtensionPlugin>

namespace QFB
{
/**
 * @internal
 * @short Login QML plugin for qfb (Qt5)
 */
class DialogsPlugin5: public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    /**
     * @internal
     * @short Register types
     * @param uri uri used in the import.
     */
    void registerTypes(const char *uri);
};

}

#endif // QFB_DIALOGS_PLUGIN5_H

