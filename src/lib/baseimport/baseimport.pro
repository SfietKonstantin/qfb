include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}import

QT = core

DEFINES += QFBBASEIMPORT_LIBRARY

INCLUDEPATH += ../base/
LIBS += -L../base/ -lqfb

# Private headers
PRIVATE_HEADERS +=  private/abstractloader_p.h \
                    private/abstractloadablemodel_p.h
# Base
PUBLIC_HEADERS +=   baseimport_global.h \
                    postvalidator.h
# Loaders
PUBLIC_HEADERS +=   loaders/abstractloader.h \
                    loaders/abstractgraphloader.h \
                    loaders/abstractgraphpostloader.h \
                    loaders/typeloader.h \
                    loaders/imageloader.h \
                    loaders/pictureloader.h \
                    loaders/albumloader.h \
                    loaders/photoloader.h \
                    loaders/userloader.h \
                    loaders/createpostloader.h
# Models
PUBLIC_HEADERS +=   models/abstractloadablemodel.h \
                    models/friendlistmodel.h \
                    models/albumlistmodel.h \
                    models/feedmodel.h \
                    models/photolistmodel.h
HEADERS +=  $${PRIVATE_HEADERS} \
            $${PUBLIC_HEADERS}

# Base
SOURCES +=  postvalidator.cpp
# Loaders
SOURCES +=  loaders/abstractloader.cpp \
            loaders/abstractgraphloader.cpp \
            loaders/abstractgraphpostloader.cpp \
            loaders/typeloader.cpp \
            loaders/imageloader.cpp \
            loaders/pictureloader.cpp \
            loaders/albumloader.cpp \
            loaders/photoloader.cpp \
            loaders/userloader.cpp \
            loaders/createpostloader.cpp
# Models
SOURCES +=  models/abstractloadablemodel.cpp \
            models/friendlistmodel.cpp \
            models/albumlistmodel.cpp \
            models/feedmodel.cpp \
            models/photolistmodel.cpp

# Deployment
target.path = $${LIBDIR}
publicHeaders.path = $${INCLUDEDIR}
publicHeaders.files = $${PUBLIC_HEADERS}
privateHeaders.path = $${INCLUDEDIR}/private
privateHeaders.files = $${PRIVATE_HEADERS}

INSTALLS += target
contains(CONFIG, dev): INSTALLS += publicHeaders privateHeaders
