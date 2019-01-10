project(dcmview)

set(DEPENDS
    dcmcore
    dcmimage
)

set(USE_QT TRUE)
set(USE_CONSOLE FALSE)
set(DEPENDS_QT Widgets)

include(build_executable)
