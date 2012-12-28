include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-mobile

QT = core gui network webkit declarative

contains(CONFIG, optify) {
QML_FOLDER = $${OPTDIR}/qml
} else {
QML_FOLDER = $${SHAREDIR}/qml
}

DEFINES += 'MAIN_QML_FILE=\'\"$${QML_FOLDER}/main.qml\"\''
DEFINES += 'IMPORT_PATH=\'\"$${IMPORTDIR}\"\''

INCLUDEPATH += ../../lib/login
INCLUDEPATH += ../../lib/base
INCLUDEPATH += ../../lib/baseimport
LIBS += -L../../lib/login -l$${NAME}login
LIBS += -L../../lib/base -l$${NAME}
LIBS += -L../../lib/baseimport -l$${NAME}import
LIBS += -L../../3rdparty/qjson/ -lqfb-qjson

HEADERS +=      tokenmanager.h \
    networkaccessmanagerfactory.h \
    networkaccessmanager.h \
    userinfohelper.h \
    posthelper.h \
    mobilepostvalidator.h

SOURCES +=      main.cpp \
                tokenmanager.cpp \
    networkaccessmanagerfactory.cpp \
    networkaccessmanager.cpp \
    userinfohelper.cpp \
    posthelper.cpp \
    mobilepostvalidator.cpp


OTHER_FILES +=  qml/main.qml \
                qml/UiConstants.js \
                qml/ClickableEntry.qml \
    qml/LoginSheet.qml \
    qml/MainPage.qml \
    qml/Banner.qml \
    qml/FriendListPage.qml \
    qml/FriendEntry.qml \
    qml/UserPage.qml \
    qml/Container.qml \
    qml/UserInfo.qml \
    qml/Feed.qml \
    qml/Post.qml \
    qml/FacebookPicture.qml

# Deployment
contains(CONFIG, optify) {
target.path = $${OPTDIR}/bin
} else {
target.path = $${BINDIR}
}

qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${OTHER_FILES}

INSTALLS += target qmlFiles
