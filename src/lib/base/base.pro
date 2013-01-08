include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}

QT = core network

DEFINES += QFBBASE_LIBRARY

INCLUDEPATH += ../../3rdparty/qjson/src/

HEADERS +=  base_global.h \
            qfb.h \
            argumentpair.h \
            helper_p.h \
            jsonhelper_p.h \
            cachehelper_p.h \
            picture_p.h \
            object.h \
            object_p.h \
            namedobject.h \
            user.h \
            language.h \
            cover.h \
            post.h \
            networkrequesthandler_p.h \
            abstractprocessor.h \
            abstractprocessor_p.h \
            abstractgraphprocessor.h \
            abstractgraphprocessor_p.h \
            abstractpagingprocessor.h \
            abstractpagingprocessor_p.h \
            request.h \
            querymanager.h \
            userprocessor.h \
            friendlistprocessor.h \
#            imagereply.h \
#            friendlistreply.h \
#            picturereply.h \
#            feedreply.h \
#    typereply.h
#    abstractpreprocessor.h \
#    abstractpreprocessor_p.h
    pictureprocessor.h \


SOURCES +=  object.cpp \
            namedobject.cpp \
            user.cpp \
            language.cpp \
            cover.cpp \
            post.cpp \
            networkrequesthandler_p.cpp \
            abstractprocessor.cpp \
            abstractgraphprocessor.cpp \
            abstractpagingprocessor.cpp \
            request.cpp \
            querymanager.cpp \
            userprocessor.cpp \
            friendlistprocessor.cpp \
#            imagereply.cpp \
#            friendlistreply.cpp \
#            picturereply.cpp \
#            feedreply.cpp \
#    typereply.cpp
#    abstractpreprocessor.cpp
    pictureprocessor.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
