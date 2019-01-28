INCLUDEPATH += $$PWD \
    $$OUT_PWD
DEPENDPATH += $$PWD \
    $$OUT_PWD

LIBS += -L../lib
DESTDIR = ../lib
lib_install.files = $$DESTDIR/$${TARGET}.dll
lib_install.path = $$(INSTALLDIR)/
INSTALLS += lib_install
