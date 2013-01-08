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
            imageprocessor.h \
            typeprocessor.h \
            pictureprocessor.h \
            userprocessor.h \
            friendlistprocessor.h \
            feedprocessor.h


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
            imageprocessor.cpp \
            typeprocessor.cpp \
            pictureprocessor.cpp \
            userprocessor.cpp \
            friendlistprocessor.cpp \
            feedprocessor.cpp

# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}
headers.files = $${HEADERS}

INSTALLS += target headers
