include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}

QT = core gui network

DEFINES += QFBBASE_LIBRARY

INCLUDEPATH += ../../3rdparty/qjson/src/
isEqual(QT_MAJOR_VERSION, 4):contains(CONFIG, noqjson):LIBS += -L$${QJSON_PATH} -lqjson
isEqual(QT_MAJOR_VERSION, 4):!contains(CONFIG, noqjson):LIBS += -L../../3rdparty/qjson/ -lqfb-qjson

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
                    private/comment_keys_p.h \
                    private/commentscontainer_keys_p.h \
                    private/cover_keys_p.h \
                    objects/likescontainer_keys_p.h \
                    private/photo_keys_p.h \
                    private/post_keys_p.h \
                    private/user_keys_p.h
# Private headers for processors
PRIVATE_HEADERS +=  private/object_creator_p.h \
                    private/abstractprocessor_p.h \
                    private/abstractgraphprocessor_p.h \
                    private/abstractpagingprocessor_p.h \
                    private/objectprocessor_p.h \
                    private/networkrequesthandler_p.h
# Base
PUBLIC_HEADERS +=   base_global.h \
                    qfb.h \
                    argumentpair.h \
                    querymanager.h \
                    request.h \
                    preprocessordata.h
# Objects
PUBLIC_HEADERS +=   objects/objectbase.h \
                    objects/object.h \
                    objects/namedobject.h \
                    objects/album.h \
                    objects/comment.h \
                    objects/commentscontainer.h \
                    objects/cover.h \
                    objects/likescontainer.h \
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
                    processors/objectprocessor.h \
                    processors/objectlistprocessor.h \
                    processors/simplecreateobjectprocessor.h

HEADERS =   $${PRIVATE_HEADERS} \
            $${PUBLIC_HEADERS}

# Base and private
SOURCES +=  private/networkrequesthandler_p.cpp \
            querymanager.cpp \
            request.cpp \
            preprocessordata.cpp
# Objects
SOURCES +=  objects/objectbase.cpp \
            objects/object.cpp \
            objects/namedobject.cpp \
            objects/album.cpp \
            objects/comment.cpp \
            objects/commentscontainer.cpp \
            objects/cover.cpp \
            objects/likescontainer.cpp \
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
            processors/objectprocessor.cpp \
            processors/objectlistprocessor.cpp \
            processors/simplecreateobjectprocessor.cpp

# Deployment
target.path = $${LIBDIR}
publicHeaders.path = $${INCLUDEDIR}
publicHeaders.files = $${PUBLIC_HEADERS}
privateHeaders.path = $${INCLUDEDIR}/private
privateHeaders.files = $${PRIVATE_HEADERS}

INSTALLS += target
contains(CONFIG, dev): INSTALLS += publicHeaders privateHeaders
