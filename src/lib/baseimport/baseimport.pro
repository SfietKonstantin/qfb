include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}import

QT = core

DEFINES += QFBBASEIMPORT_LIBRARY

INCLUDEPATH += ../base/
LIBS += -L../base/ -lqfb

HEADERS +=  baseimport_global.h \
            abstractloader.h \
            abstractloader_p.h \
            abstractgraphloader.h \
            abstractloadablemodel.h \
            imageloader.h \
            typeloader.h \
            pictureloader.h \
            userloader.h \
            friendlistmodel.h \
            postvalidator.h \
            feedmodel.h \
    albumloader.h \
            albumlistmodel.h \
            photolistmodel.h \

SOURCES +=  abstractloader.cpp \
            abstractgraphloader.cpp \
            abstractloadablemodel.cpp \
            imageloader.cpp \
            typeloader.cpp \
            pictureloader.cpp \
            userloader.cpp \
            friendlistmodel.cpp \
            postvalidator.cpp \
            feedmodel.cpp \
    albumloader.cpp \
            albumlistmodel.cpp \
            photolistmodel.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
