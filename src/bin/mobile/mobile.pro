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
!contains(CONFIG, noqjson):LIBS += -L../../3rdparty/qjson/ -lqfb-qjson

HEADERS +=      tokenmanager.h \
    networkaccessmanagerfactory.h \
    networkaccessmanager.h \
    userinfohelper.h \
    posthelper.h \
    mobilepostvalidator.h \
    pagemanagementbridge.h

SOURCES +=      main.cpp \
                tokenmanager.cpp \
    networkaccessmanagerfactory.cpp \
    networkaccessmanager.cpp \
    userinfohelper.cpp \
    posthelper.cpp \
    mobilepostvalidator.cpp \
    pagemanagementbridge.cpp


OTHER_FILES +=  qml/main.qml \
                qml/UiConstants.js \
                qml/ClickableEntry.qml \
                qml/FacebookImage.qml \
                qml/FacebookPicture.qml \
                qml/Banner.qml \
                qml/Container.qml \
                qml/Post.qml \
                qml/Feed.qml \
                qml/LoginSheet.qml \
                qml/NewsPage.qml \
                qml/MainPage.qml \
                qml/UserInfo.qml \
                qml/UserPage.qml \
                qml/FriendEntry.qml \
                qml/FriendListPage.qml \
    qml/TypePage.qml \
    qml/UserInfoPage.qml \
    qml/AlbumListPage.qml \
    qml/AlbumList.qml \
    qml/AlbumEntry.qml \
    qml/PhotoListPage.qml \
    qml/PhotoList.qml \
    qml/PhotoBrowserPage.qml

# Deployment
contains(CONFIG, optify) {
target.path = $${OPTDIR}/bin
} else {
target.path = $${BINDIR}
}

qmlFiles.path = $${QML_FOLDER}
qmlFiles.files = $${OTHER_FILES}

INSTALLS += target qmlFiles

contains(MEEGO_EDITION, harmattan) {
    desktopFile.files = qfb.desktop
    desktopFile.path = /usr/share/applications

    icon.files = qfb.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    INSTALLS += desktopFile icon
}
