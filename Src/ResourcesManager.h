#pragma once

#include "Building.h"
#include "Resources.h"
#include "EventProcessable.h"
#include "StlVector/Src/Vector.hpp"

// Every tick update resources from buildings
// Kill program if population less then zero
class ResourcesManager : public EventProcessable
{    
    void onTick() override;
private:
    Resources         user_res;
    Vector<Building*> buildings;
};
