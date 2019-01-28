TEMPLATE = subdirs
SUBDIRS += \
    core \
#    qsradar \
    testradar \
    ppiview \
    eview \
    plotwatch \
    tracklistview \
    replay

    core.subdir = core
    core.depends =
    qsradar.subdir = qsradar
    qsradar.depends = core
    ppiview.subdir = ppiview
    ppiview.depends = core
    plotwatch.subdir = plotwatch
    plotwatch.depends = core
    tracklistview.subdir = tracklistview
    tracklistview.depends = core
    testradar.subdir = testradar
    testradar.depends = core
    replay.subdir = replay
    replay.depends = core
    eview.subdir = eview
    eview.depends = core
