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
    me.h

SOURCES +=      main.cpp \
                tokenmanager.cpp \
    networkaccessmanagerfactory.cpp \
    networkaccessmanager.cpp \
    userinfohelper.cpp \
    posthelper.cpp \
    mobilepostvalidator.cpp \
    me.cpp

QML_ROOT +=         qml/main.qml \
                    qml/UiConstants.js \
                    qml/pagemanagement.js

QML_COMPONENTS +=   qml/components/FacebookImage.qml \
                    qml/components/FacebookPicture.qml \
                    qml/components/LoadingIndicator.qml \
                    qml/components/LoadingMessage.qml \
                    qml/components/LoadingButton.qml \
                    qml/components/EmptyStateLabel.qml \
                    qml/components/ClickableEntry.qml \
                    qml/components/FriendEntry.qml \
                    qml/components/CommentEntry.qml \
                    qml/components/Cover.qml \
                    qml/components/Container.qml \
                    qml/components/Post.qml \
                    qml/components/AlbumEntry.qml

QML_COMPOSITE +=    qml/composite/UserInfo.qml \
                    qml/composite/PostList.qml \
                    qml/composite/AlbumList.qml \
                    qml/composite/PhotoList.qml

QML_PAGES +=        qml/pages/MainPage.qml \
                    qml/pages/NewsPage.qml \
                    qml/pages/FriendListPage.qml \
                    qml/pages/AlbumListPage.qml \
                    qml/pages/PhotoListPage.qml \
                    qml/pages/PhotoViewerPage.qml \
                    qml/pages/PostPage.qml \
                    qml/pages/UserPage.qml \
                    qml/pages/UserInfoPage.qml

QML_DIALOGS +=      qml/dialogs/LoginSheet.qml \
                    qml/dialogs/FeedDialogSheet.qml

OTHER_FILES +=  $${QML_ROOT} $${QML_COMPONENTS} $${QML_COMPOSITE} $${QML_PAGES} $${QML_DIALOGS}

# Deployment
contains(CONFIG, optify) {
target.path = $${OPTDIR}/bin
} else {
target.path = $${BINDIR}
}

qmlRootFiles.path = $${QML_FOLDER}
qmlRootFiles.files = $${QML_ROOT}

qmlComponentsFiles.path = $${QML_FOLDER}/components
qmlComponentsFiles.files = $${QML_COMPONENTS}

qmlCompositeFiles.path = $${QML_FOLDER}/composite
qmlCompositeFiles.files = $${QML_COMPOSITE}

qmlPagesFiles.path = $${QML_FOLDER}/pages
qmlPagesFiles.files = $${QML_PAGES}

qmlDialogsFiles.path = $${QML_FOLDER}/dialogs
qmlDialogsFiles.files = $${QML_DIALOGS}

INSTALLS += target qmlRootFiles qmlComponentsFiles qmlCompositeFiles qmlPagesFiles qmlDialogsFiles

contains(MEEGO_EDITION, harmattan) {
    desktopFile.files = qfb.desktop
    desktopFile.path = /usr/share/applications

    icon.files = qfb.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    INSTALLS += desktopFile icon
}
