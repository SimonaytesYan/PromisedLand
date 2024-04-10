#pragma once

//=============PROGRAM SETTINGS=============
#ifndef USES_SFML
#define USES_SFML 1
#endif

static const char* kWindowHeader  = "Promised Lands";
static const int         kControlPanelH = 150;
static const int         kControlPanelW = 150;
static const int         kTextSize      = 20;
static const int         kMSInClock     = 1000;

//=============CELL TYPES=============
enum class FieldType
{
    Grass,
    Water,
    House,
    Sawmill,
    Well,
    Windmill,
    FieldNumber,
    Error
};