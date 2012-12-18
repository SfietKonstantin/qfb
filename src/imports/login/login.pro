include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        $${NAME}loginplugin
QT =            core gui
isEqual(QT_MAJOR_VERSION, 4): QT += declarative
isEqual(QT_MAJOR_VERSION, 5): QT += qml

CONFIG +=       qt plugin

INCLUDEPATH +=  ../../lib/login/
LIBS +=         -L ../../lib/login/ -l$${NAME}login

isEqual(QT_MAJOR_VERSION, 4): HEADERS += login_plugin4.h
isEqual(QT_MAJOR_VERSION, 5): HEADERS += login_plugin5.h

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


