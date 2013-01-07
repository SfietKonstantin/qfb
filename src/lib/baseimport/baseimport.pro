include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}import

QT = core

DEFINES += QFBBASEIMPORT_LIBRARY

INCLUDEPATH += ../base/

HEADERS +=  baseimport_global.h \
            abstractloader.h \
            abstractloader_p.h \
            abstractgraphloader.h \
            abstractloadablemodel.h \
            userloader.h \
            friendlistmodel.h \
            postvalidator.h

SOURCES +=  abstractloader.cpp \
            abstractgraphloader.cpp \
            abstractloadablemodel.cpp \
            userloader.cpp \
            friendlistmodel.cpp \
            postvalidator.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
