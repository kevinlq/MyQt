bin_rcc.name = bin_rcc
bin_rcc.input = RCC_RESOURCES
bin_rcc.output = ${QMAKE_FILE_IN_BASE}.rcc
bin_rcc.commands = rcc -binary ${QMAKE_FILE_IN} -o ${QMAKE_FILE_OUT}
silent:bin_rcc.commands = @echo rcc ${QMAKE_FILE_IN} && $$bin_rcc.commands
bin_rcc.CONFIG = no_link target_predeps
QMAKE_EXTRA_COMPILERS += bin_rcc
