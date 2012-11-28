include(../../../globals.pri)

TEMPLATE = lib
TARGET = qjson

INCLUDE_HEADERS +=  src/parser.h \
                    src/qobjecthelper.h \
                    src/parserrunnable.h \
                    src/serializer.h \
                    src/serializerrunnable.h

HEADERS +=  $${INCLUDE_HEADERS} \
            src/json_parser.hh \
            src/location.hh \
            src/position.hh \
            src/stack.hh \
            src/json_scanner.h \

SOURCES +=  src/parser.cpp \
            src/qobjecthelper.cpp \
            src/json_scanner.cpp \
            src/json_parser.cc \
            src/parserrunnable.cpp \
            src/serializer.cpp \
            src/serializerrunnable.cpp

# Deployment
target.path = $${LIBDIR}
export(target.path)

includeHeaders.files = $${INCLUDE_HEADERS}
includeHeaders.path = $${INCLUDEDIR}/qjson
export(includeHeaders.files)
export(includeHeaders.path)

INSTALLS += target includeHeaders
