#pragma once

#include "Field.h"
#include "IncodeOutcome.h"
#include "../Resources.h"

const char* kFieldsAssets[] = {"Assets/field.png",
                               "Assets/water.png",
                               "Assets/house.png",
                               "Assets/sawmill.png",
                               "Assets/well.png",
                               "Assets/windmill.png"};

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

FIELD(Grass,    Resources( 0,  0,   0, 0), Resources( 0,  0, 0, 0), kFieldsAssets[0])
FIELD(Water,    Resources( 0,  0,   0, 0), Resources( 0,  0, 0, 0), kFieldsAssets[1])
FIELD(House,    Resources( 0,  0, -15, 5), Resources(-5, -5, 0, 0), kFieldsAssets[2])
FIELD(Sawmill,  Resources( 0,  0, -10, 0), Resources( 0,  0, 2, 0), kFieldsAssets[3])
FIELD(Well,     Resources( 0,  0, -10, 0), Resources( 0, 20, 0, 0), kFieldsAssets[4])
FIELD(Windmill, Resources( 0,  0, -10, 0), Resources(20,  0, 0, 0), kFieldsAssets[5])
