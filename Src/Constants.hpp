#pragma once

//=============PROGRAM SETTINGS=============
#ifndef USES_SFML
#define USES_SFML 1
#endif

static const char* kWindowHeader       = "Promised Lands";
static const int   kControlPanelH      = 150;
static const int   kControlPanelW      = 150;
static const int   kControlPanelYStart = 100;
static const int   kTextSize           = 20;
static const int   kMSInClock          = 1000;

//=============CELL TYPES=============

#define CELL_LOGIC(name, ...)       \
    name,

#define BUILDING_LOGIC(name, ...)   \
    name,

enum class FieldType
{
    #include "GameLogic/Tiles/CellPreforms.hpp"
    FieldNumber,
    Error
};

#undef CELL_LOGIC
#undef BUILDING_LOGIC
