TEMPLATE = subdirs
contains(QT_VERSION, ^4\\.\\d+\\.\\d+$): SUBDIRS = 3rdparty
SUBDIRS += lib imports bin
