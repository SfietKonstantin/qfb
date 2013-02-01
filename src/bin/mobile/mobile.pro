include(../../../globals.pri)

TEMPLATE = app
TARGET = $${NAME}-mobile

QT = core gui network declarative

contains(CONFIG, optify) {
QML_FOLDER = $${OPTDIR}/qml
DATA_FOLDER = $${OPTDIR}/data
} else {
QML_FOLDER = $${SHAREDIR}/qml
DATA_FOLDER = $${SHAREDIR}/data
}

DEFINES += 'MAIN_QML_FILE=\'\"$${QML_FOLDER}/main.qml\"\''
!contains(MEEGO_EDITION, harmattan) {
DEFINES += 'IMPORT_PATH=\'\"$${IMPORTDIR}\"\''
}
DEFINES += 'DATA_PATH=\'\"$${DATA_FOLDER}/\"\''

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

QML_COMPONENTS +=   qml/components/Separator.qml \
                    qml/components/GroupIndicator.qml \
                    qml/components/FacebookImage.qml \
                    qml/components/FacebookPicture.qml \
                    qml/components/LoadingIndicator.qml \
                    qml/components/LoadingMessage.qml \
                    qml/components/LoadingButton.qml \
                    qml/components/EmptyStateLabel.qml \
                    qml/components/ClickableEntry.qml \
                    qml/components/FriendEntry.qml \
                    qml/components/GroupBookmarkEntry.qml \
                    qml/components/CommentEntry.qml \
                    qml/components/Cover.qml \
                    qml/components/Container.qml \
                    qml/components/Post.qml \
                    qml/components/AlbumEntry.qml \
                    qml/components/PostTextArea.qml

QML_COMPOSITE +=    qml/composite/UserInfo.qml \
                    qml/composite/PostList.qml \
                    qml/composite/AlbumList.qml \
                    qml/composite/PhotoList.qml

QML_PAGES +=        qml/pages/MainPage.qml \
                    qml/pages/AboutPage.qml \
                    qml/pages/DevelopersPage.qml \
                    qml/pages/NewsPage.qml \
                    qml/pages/AlbumListPage.qml \
                    qml/pages/FriendListPage.qml \
                    qml/pages/GroupPage.qml \
                    qml/pages/GroupListPage.qml \
                    qml/pages/LikesPage.qml \
                    qml/pages/PhotoListPage.qml \
                    qml/pages/PhotoViewerPage.qml \
                    qml/pages/PostPage.qml \
                    qml/pages/UserPage.qml \
                    qml/pages/UserInfoPage.qml

QML_DIALOGS +=      qml/dialogs/LoginSheet.qml \
                    qml/dialogs/FeedDialogSheet.qml

DATA_FILES +=       data/friends.png \
                    data/developers.png \
                    data/comment-black.png \
                    data/comment-white.png \
                    data/like-black.png \
                    data/like-white.png \
                    data/unlike-black.png \
                    data/unlike-white.png \
                    data/sfiet_konstantin.jpg \
                    data/aniket.jpg

OTHER_FILES +=      $${QML_ROOT} \
                    $${QML_COMPONENTS} \
                    $${QML_COMPOSITE} \
                    $${QML_PAGES} \
                    $${QML_DIALOGS} \
                    $${DATA_FILES}

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

dataFiles.path = $${DATA_FOLDER}
dataFiles.files = $${DATA_FILES}

INSTALLS +=     target \
                qmlRootFiles \
                qmlComponentsFiles \
                qmlCompositeFiles \
                qmlPagesFiles \
                qmlDialogsFiles \
                dataFiles

contains(MEEGO_EDITION, harmattan) {
    desktopFile.files = qfb.desktop
    desktopFile.path = /usr/share/applications

    icon.files = qfb.png
    icon.path = /usr/share/icons/hicolor/80x80/apps

    INSTALLS += desktopFile icon
}
