include($$PWD/QSharedMemoryDemo.pri)

TEMPLATE  = subdirs
CONFIG   += ordered

SUBDIRS += \
    $$PWD/MasterProcess \
    $$PWD/ChildProcess
