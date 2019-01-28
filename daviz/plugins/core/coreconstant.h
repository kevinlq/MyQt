#ifndef CORECONSTANT_H
#define CORECONSTANT_H

#include <QtGlobal>

namespace RadarDisplay {

static const char RADAR_MENU_NAME[] = QT_TRANSLATE_NOOP("Menu", "Radar");
static const int RADAR_MENU_PRIORITY = 0;

static const char HELP_MENU_NAME[] = QT_TRANSLATE_NOOP("Menu", "Help");
static const int HELP_MENU_PRIORITY = 100;

static const int VIEW_LABEL_LEADING = 0;
static const int VIEW_LABEL_WIDTH = 70;

static const int VIEW_PANEL_PRIORITY = 0;
static const int PLOT_PANEL_PRIORITY = 100;
static const int TRACK_PANEL_PRIORITY = 200;
static const int REPLAY_PANEL_PRIORITY = 300;
}

#endif // CORECONSTANT_H
