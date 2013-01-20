include(../../../globals.pri)

TEMPLATE = lib
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}

TARGET = $${NAME}dialogs

QT = core

DEFINES += QFBDIALOGS_LIBRARY

HEADERS +=  dialogs_global.h \
            feeddialogmanager.h
SOURCES +=  feeddialogmanager.cpp



# Deployment
target.path = $${LIBDIR}

headers.path = $${INCLUDEDIR}/dialogs
headers.files = $${HEADERS}

INSTALLS += target
contains(CONFIG, dev): INSTALLS += headers
