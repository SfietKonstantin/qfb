include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}

QT = core gui network

DEFINES += QFBBASE_LIBRARY

INCLUDEPATH += ../../3rdparty/qjson/src/
contains(CONFIG, noqjson):LIBS += -L$${QJSON_PATH} -lqjson
!contains(CONFIG, noqjson):LIBS += -L../../3rdparty/qjson/ -lqfb-qjson

# Helpers
PRIVATE_HEADERS +=  private/helper_p.h \
                    private/jsonhelper_p.h \
                    private/cachehelper_p.h \
                    private/picture_p.h \
                    private/paging_keys_p.h
# Private headers for objects
PRIVATE_HEADERS +=  private/objectbase_p.h \
                    private/object_keys_p.h \
                    private/object_type_keys_p.h \
                    private/namedobject_keys_p.h \
                    private/album_keys_p.h \
                    private/cover_keys_p.h \
                    private/photo_keys_p.h \
                    private/post_keys_p.h \
                    private/user_keys_p.h
# Private headers for processors
PRIVATE_HEADERS +=  private/abstractprocessor_p.h \
                    private/abstractgraphprocessor_p.h \
                    private/abstractpagingprocessor_p.h \
                    private/albumprocessor_p.h \
                    private/photoprocessor_p.h \
                    private/networkrequesthandler_p.h
# Base
PUBLIC_HEADERS +=   base_global.h \
                    qfb.h \
                    argumentpair.h \
                    querymanager.h \
                    request.h
# Objects
PUBLIC_HEADERS +=   objects/objectbase.h \
                    objects/object.h \
                    objects/namedobject.h \
                    objects/album.h \
                    objects/cover.h \
                    objects/photo.h \
                    objects/post.h \
                    objects/user.h
# Processors
PUBLIC_HEADERS +=   processors/abstractprocessor.h \
                    processors/abstractgraphprocessor.h \
                    processors/abstractpagingprocessor.h \
                    processors/imageprocessor.h \
                    processors/typeprocessor.h \
                    processors/pictureprocessor.h \
                    processors/albumprocessor.h \
                    processors/albumlistprocessor.h \
                    processors/feedprocessor.h \
                    processors/friendlistprocessor.h \
                    processors/photoprocessor.h \
                    processors/photolistprocessor.h \
                    processors/userprocessor.h

HEADERS =   $${PRIVATE_HEADERS} \
            $${PUBLIC_HEADERS}

# Base and private
SOURCES +=  private/networkrequesthandler_p.cpp \
            querymanager.cpp \
            request.cpp
# Objects
SOURCES +=  objects/objectbase.cpp \
            objects/object.cpp \
            objects/namedobject.cpp \
            objects/album.cpp \
            objects/cover.cpp \
            objects/photo.cpp \
            objects/post.cpp \
            objects/user.cpp
# Processors
SOURCES +=  processors/abstractprocessor.cpp \
            processors/abstractgraphprocessor.cpp \
            processors/abstractpagingprocessor.cpp \
            processors/imageprocessor.cpp \
            processors/typeprocessor.cpp \
            processors/pictureprocessor.cpp \
            processors/albumprocessor.cpp \
            processors/albumlistprocessor.cpp \
            processors/feedprocessor.cpp \
            processors/friendlistprocessor.cpp \
            processors/photoprocessor.cpp \
            processors/photolistprocessor.cpp \
            processors/userprocessor.cpp

# Deployment
target.path = $${LIBDIR}
publicHeaders.path = $${INCLUDEDIR}
publicHeaders.files = $${PUBLIC_HEADERS}
privateHeaders.path = $${INCLUDEDIR}/private
privateHeaders.files = $${PRIVATE_HEADERS}

INSTALLS += target
contains(CONFIG, dev): INSTALLS += publicHeaders privateHeaders
