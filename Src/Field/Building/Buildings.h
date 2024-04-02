#pragma once

#include "Building.h"
#include "IncodeOutcome.h"
#include "../../Resources.h"

BUILDING(House,    Resources( 0,  0, -15, 5), Resources(-5, -5, 0, 0), "Assets/house.png")
BUILDING(Sawmill,  Resources( 0,  0, -10, 0), Resources( 0,  0, 2, 0), "Assets/sawmill.png")
BUILDING(Well,     Resources( 0,  0, -10, 0), Resources( 0, 20, 0, 0), "Assets/well.png")
BUILDING(Windmill, Resources( 0,  0, -10, 0), Resources(20,  0, 0, 0), "Assets/windmill.png")
