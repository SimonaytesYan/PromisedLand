#pragma once

#include <iostream>

#include "Field/Building/Building.h"
#include "Resources.h"
#include "EventProcessable.h"
#include "../StlVector/Src/Vector.hpp"

// Every tick update resources from buildings
// Kill program if population less then zero
class ResourcesManager : public EventProcessable
{    
public:
    explicit ResourcesManager(Resources start_resources) 
      : user_res (start_resources) {}

    void onClick(int x, int y) override {}
    void onTick()              override 
    {  
        for (size_t i = 0; i < buildings.Size(); ++i)
        {
            user_res += buildings[i]->getTickIncome();
        }
    }

    Resources getUserRes()
    { return user_res; }

    void addBuilding(Building* building) 
    { buildings.PushBack(building); }

private:
    Resources         user_res;
    Vector<Building*> buildings;
};
