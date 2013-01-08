include(../../../globals.pri)

TEMPLATE =      lib

TARGET =        $${NAME}plugin
QT =            core gui
isEqual(QT_MAJOR_VERSION, 4): QT += declarative
isEqual(QT_MAJOR_VERSION, 5): QT += qml

CONFIG +=       qt plugin

INCLUDEPATH +=  ../../lib/base/
INCLUDEPATH += ../../lib/baseimport
LIBS +=         -L ../../lib/base/ -l$${NAME}
LIBS += -L../../lib/baseimport -l$${NAME}import

#HEADERS +=      abstractloadablemodel.h \
#                abstractloadablemodel_p.h \
#                friendlistmodel.h \
#                feedmodel.h \
#HEADERS += loaderbase.h \
#                loaderbase.h \
#                loaderbase_p.h \
#HEADERS += abstractloader.h \
#                abstractloader.h \
#                imageloader.h \
#                abstractgraphloader.h \
#                pictureloader.h \
#                userloader.h \
#    typeloader.h
#    abstractloader_p.h
#HEADERS += friendlistmodel.h
#HEADERS += pictureloader.h

isEqual(QT_MAJOR_VERSION, 4): HEADERS += base_plugin4.h
isEqual(QT_MAJOR_VERSION, 5): HEADERS += base_plugin5.h

SOURCES +=      base_plugin.cpp \
#                abstractloadablemodel.cpp \
#                friendlistmodel.cpp \
#                feedmodel.cpp \
#                loaderbase.cpp \
#                abstractloader.cpp \
#                imageloader.cpp \
#                abstractgraphloader.cpp \
#                pictureloader.cpp \
#                userloader.cpp \
#    typeloader.cpp

OTHER_FILES =   qmldir \

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


