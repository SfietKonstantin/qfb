include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        $${NAME}plugin
QT =            core gui
isEqual(QT_MAJOR_VERSION, 4): QT += declarative
isEqual(QT_MAJOR_VERSION, 5): QT += qml

CONFIG +=       qt plugin

INCLUDEPATH +=  ../../lib/base/
LIBS +=         -L ../../lib/base/ -l$${NAME}

HEADERS +=      friendlistmodel.h \
                pictureloader.h \
                userloader.h
isEqual(QT_MAJOR_VERSION, 4): HEADERS += base_plugin4.h
isEqual(QT_MAJOR_VERSION, 5): HEADERS += base_plugin5.h

SOURCES +=      base_plugin.cpp \
                friendlistmodel.cpp \
                pictureloader.cpp \
                userloader.cpp

OTHER_FILES =   qmldir

# Path for QML files
qmlFiles.path = $${QML_PLUGIN_PATH}
qmlFiles.files = $${OTHER_FILES}
export(qmlFiles.path)
export(qmlFiles.files)

# Path for target
target.path = $${QML_PLUGIN_PATH}
export(target.path)

# Installs
INSTALLS += target qmlFiles


