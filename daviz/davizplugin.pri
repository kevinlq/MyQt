include(utils/utils.pri)
include(extensionsystem/extensionsystem.pri)
CONFIG += plugin

INCLUDEPATH += $$_PRO_FILE_PWD_/../
INCLUDEPATH += $$PWD \
    $$OUT_PWD
DEPENDPATH += $$PWD \
    $$OUT_PWD

win32 {
    debug {
        OUT_SUBDIR = debug
        DLL_SUFFIX = d
    }
    else {
        OUT_SUBDIR = release
    }
}

LIBS += -L../lib -L../../lib

PLUGINSPEC = $$_PRO_FILE_PWD_/$${TARGET}.pluginspec
PLUGINSPEC_IN = $${PLUGINSPEC}.in
exists($$PLUGINSPEC_IN) {
    OTHER_FILES += $$PLUGINSPEC_IN
    QMAKE_SUBSTITUTES += $$PLUGINSPEC_IN
    PLUGINSPEC = $$OUT_PWD/$${TARGET}.pluginspec
#    copy2build.output = $$OUT_DIR/plugins/$${TARGET}.pluginspec
} else {
    # need to support that for external plugins
    OTHER_FILES += $$PLUGINSPEC
#    copy2build.output = $$OUT_DIR/plugins/$${TARGET}.pluginspec
    copy2build.output = $$OUT_PWD/$${TARGET}.pluginspec
}
copy2build.input = PLUGINSPEC
copy2build.variable_out = PRE_TARGETDEPS
copy2build.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copy2build.name = COPY ${QMAKE_FILE_IN}
copy2build.CONFIG += no_link
QMAKE_EXTRA_COMPILERS += copy2build

DESTDIR = ../lib
plugin_install.files += $$DESTDIR/$${TARGET}.dll
plugin_install.files += $$copy2build.output
plugin_install.path = $$(INSTALLDIR)/plugins
INSTALLS += plugin_install
