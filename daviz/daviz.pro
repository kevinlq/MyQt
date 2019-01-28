TEMPLATE = subdirs
CONFIG += ordered silent

SUBDIRS += \
    extensionsystem \
    utils \
    app \
    plugins \

OTHER_FILES += davizplugin.pri \
    davizlib.pri
