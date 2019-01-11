project(dcmnet)

set(QT_DONT_USE_QTGUI TRUE)
set(QT_USE_QTNETWORK TRUE)

set(LIBS dcmcore)

set(MOCS DcmSCU.h)

include(build_shared_lib)
include(build_test)
include(build_doc)
