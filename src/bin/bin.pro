TEMPLATE = subdirs
contains(QT_VERSION, ^4\\.\\d+\\.\\d+$): SUBDIRS = demo4
contains(QT_VERSION, ^5\\.\\d+\\.\\d+$): SUBDIRS = demo5
contains(CONFIG, mobile): SUBDIRS = mobile
