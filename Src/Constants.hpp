#pragma once

//=============PROGRAM SETTINGS=============
#ifndef USES_SFML
#define USES_SFML 1
#endif

static const char* kPluginFolder = "PluginObjects";

static const char* kWindowHeader       = "Promised Lands";
static const int   kControlPanelH      = 150;
static const int   kControlPanelW      = 150;
static const int   kControlPanelYStart = 200;
static const int   kTextSize           = 20;
static const int   kMSInClock          = 1000;

static const int x_cell_cnt = 10;
static const int y_cell_cnt = 10;

static int visible_part_x = 0;
static int visible_part_y = 0;
