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
            jsonhelper_p.h \
            object.h \
            object_p.h \
            userbase.h \
            user.h \
            language.h \
            status.h \
            abstractreply.h \
            abstractreply_p.h \
            friendlistreply.h \
            querymanager.h \
            picture_p.h \
            picturereply.h \
            userreply.h \
    feedreply.h \
    post.h \
    cover.h

SOURCES +=  object.cpp \
            userbase.cpp \
            user.cpp \
            language.cpp \
            status.cpp \
            abstractreply.cpp \
            friendlistreply.cpp \
            querymanager.cpp \
            picturereply.cpp \
            userreply.cpp \
    feedreply.cpp \
    post.cpp \
    cover.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
