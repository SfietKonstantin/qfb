TEMPLATE = subdirs
isEqual(QT_MAJOR_VERSION, 4): SUBDIRS = demo4
isEqual(QT_MAJOR_VERSION, 5): SUBDIRS = demo5
contains(CONFIG, mobile): SUBDIRS = mobile
