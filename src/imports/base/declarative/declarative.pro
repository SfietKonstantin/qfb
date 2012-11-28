include(../../../../globals.pri)

TEMPLATE =      lib

TARGET =        $${NAME}plugin
QT =            core gui declarative

CONFIG +=       qt plugin

INCLUDEPATH +=  ../../../lib/base/
LIBS +=         -L ../../../lib/base/ -l$${NAME}

HEADERS +=      base_plugin.h
SOURCES +=      base_plugin.cpp

OTHER_FILES =   ../common/qmldir

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
