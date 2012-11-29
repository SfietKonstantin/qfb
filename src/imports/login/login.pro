include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        $${NAME}loginplugin
QT =            core gui
contains(QT_VERSION, ^4\\.\\d+\\.\\d+$): QT += declarative
contains(QT_VERSION, ^5\\.\\d+\\.\\d+$): QT += qml

CONFIG +=       qt plugin

INCLUDEPATH +=  ../../lib/login/
LIBS +=         -L ../../lib/login/ -l$${NAME}login

contains(QT_VERSION, ^4\\.\\d+\\.\\d+$): HEADERS += login_plugin4.h
contains(QT_VERSION, ^5\\.\\d+\\.\\d+$): HEADERS += login_plugin5.h

SOURCES +=      login_plugin.cpp \

OTHER_FILES =   qmldir

# Path for QML files
qmlFiles.path = $${QML_PLUGIN_PATH}/login
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for target
target.path = $${QML_PLUGIN_PATH}/login
export(target.path)

# Installs
INSTALLS += target qmlFiles


