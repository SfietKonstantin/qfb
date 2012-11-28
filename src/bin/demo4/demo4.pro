include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-demo

QT = core gui webkit declarative

QML_FOLDER = $${SHAREDIR}/qml

DEFINES += 'MAIN_QML_FILE=\'\"$${QML_FOLDER}/main.qml\"\''
DEFINES += 'IMPORT_PATH=\'\"$${IMPORTDIR}\"\''

INCLUDEPATH += ../../lib/login
INCLUDEPATH += ../../lib/base
LIBS += -L../../lib/login -l$${NAME}login
LIBS += -L../../lib/base -l$${NAME}
LIBS += -L../../3rdparty/qjson/ -lqjson

HEADERS +=  bridge.h

SOURCES +=  main.cpp \
            bridge.cpp


OTHER_FILES +=  main.qml

# Deployment
target.path = $${BINDIR}

qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${OTHER_FILES}

INSTALLS += target qmlFiles

