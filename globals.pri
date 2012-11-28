# name
NAME = qfb

# version
VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_PATCH = 0

isEmpty(DEPLOYMENT_PREFIX) {
    DEPLOYMENT_PREFIX = /usr
}

isEmpty(PREFIX) {
    CONFIG(release):PREFIX = /usr
    CONFIG(debug, debug|release):PREFIX = $${DEPLOYMENT_PREFIX}
}

DEFAULT_IMPORT_FOLDER = /usr/lib/qt4/imports/

# Default directories
isEmpty(BINDIR) {
    BINDIR = $${PREFIX}/bin
}
isEmpty(LIBDIR) {
    LIBDIR = $${PREFIX}/lib
}
isEmpty(IMPORTDIR) {
    CONFIG(noqtimport):{
        IMPORTDIR = $${PREFIX}/imports/
    } else {
        IMPORTDIR = $${DEFAULT_IMPORT_FOLDER}
    }
}
isEmpty(SHAREDIR) {
    SHAREDIR = $${PREFIX}/share/$${NAME}
}

isEmpty(OPTDIR) {

    OPTDIR = /opt/$${NAME}
}

isEmpty(INCLUDEDIR) {
    INCLUDEDIR = $${PREFIX}/include/$${NAME}
}

# QML include folder
QML_PLUGIN_BASE_PATH = $${IMPORTDIR}/org/SfietKonstantin/
QML_PLUGIN_PATH = $${QML_PLUGIN_BASE_PATH}/$${NAME}


# Useful defines
DEFINES += 'VERSION_MAJOR=$${VERSION_MAJOR}'
DEFINES += 'VERSION_MINOR=$${VERSION_MINOR}'
DEFINES += 'VERSION_PATCH=$${VERSION_PATCH}'
