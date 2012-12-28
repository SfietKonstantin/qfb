include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}import

QT = core

DEFINES += QFBBASEIMPORT_LIBRARY

INCLUDEPATH += ../base/

HEADERS +=  baseimport_global.h \
            postvalidator.h

SOURCES +=  postvalidator.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
