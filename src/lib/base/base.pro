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
            namedobject.h \
            user.h \
            language.h \
            cover.h \
            post.h \
            abstractreply.h \
            abstractreply_p.h \
            imagereply.h \
            abstractgraphreply.h \
            abstractgraphreply_p.h \
            friendlistreply.h \
            querymanager.h \
            picture_p.h \
            picturereply.h \
            userreply.h \
            feedreply.h \
    abstractgraphpagingreply.h \
    abstractgraphpagingreply_p.h \

SOURCES +=  object.cpp \
            namedobject.cpp \
            user.cpp \
            language.cpp \
            cover.cpp \
            post.cpp \
            abstractreply.cpp \
            imagereply.cpp \
            abstractgraphreply.cpp \
            friendlistreply.cpp \
            querymanager.cpp \
            picturereply.cpp \
            userreply.cpp \
            feedreply.cpp \
    abstractgraphpagingreply.cpp \

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
