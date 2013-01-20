include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        $${NAME}dialogsplugin
QT =            core gui
isEqual(QT_MAJOR_VERSION, 4): QT += declarative
isEqual(QT_MAJOR_VERSION, 5): QT += qml

CONFIG +=       qt plugin

INCLUDEPATH +=  ../../lib/dialogs/
LIBS +=         -L ../../lib/dialogs/ -l$${NAME}dialogs

isEqual(QT_MAJOR_VERSION, 4): HEADERS += dialogs_plugin4.h
isEqual(QT_MAJOR_VERSION, 5): HEADERS += dialogs_plugin5.h

SOURCES +=      dialogs_plugin.cpp \

OTHER_FILES =   qmldir

# Path for QML files
qmlFiles.path = $${QML_PLUGIN_PATH}/dialogs
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for target
target.path = $${QML_PLUGIN_PATH}/dialogs
export(target.path)

# Installs
INSTALLS += target qmlFiles


