include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}

QT = core network

DEFINES += QFBBASE_LIBRARY

INCLUDEPATH += ../../3rdparty/qjson/src/

HEADERS +=  base_global.h \
            qfb.h \
            helper_p.h \
            object.h \
            object_p.h \
            userbase.h \
            abstractreply.h \
            abstractreply_p.h \
            friendlistreply.h \
            querymanager.h \
            picture_p.h \
            picturereply.h \
    user.h \
    userreply.h

SOURCES +=  object.cpp \
            userbase.cpp \
            abstractreply.cpp \
            friendlistreply.cpp \
            querymanager.cpp \
            picturereply.cpp \
    user.cpp \
    userreply.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
