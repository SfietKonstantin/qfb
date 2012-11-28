include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}

QT = core network

DEFINES += QFBBASE_LIBRARY

INCLUDEPATH += ../../3rdparty/qjson/src/

HEADERS +=  base_global.h \
            object.h \
            object_p.h \
            friendbase.h \
            friendbase_p.h \
            abstractreply.h \
            abstractreply_p.h \
            friendlistreply.h \
            querymanager.h

SOURCES +=  object.cpp \
            friendbase.cpp \
            abstractreply.cpp \
            friendlistreply.cpp \
            querymanager.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
