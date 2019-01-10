project(dcmimage)

set(USE_QT TRUE)
set(DEPENDS_QT Core Widgets)

set(DEPENDS dcmcore)

include(build_shared_library)
