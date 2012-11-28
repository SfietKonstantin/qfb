TEMPLATE = subdirs
contains(QT_VERSION, ^4\\.\\d+\\.\\d+$): SUBDIRS += declarative
contains(QT_VERSION, ^5\\.\\d+\\.\\d+$): SUBDIRS += qml
