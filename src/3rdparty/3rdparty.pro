TEMPLATE = subdirs
isEqual(QT_MAJOR_VERSION, 4):!contains(CONFIG, noqjson):SUBDIRS += qjson
