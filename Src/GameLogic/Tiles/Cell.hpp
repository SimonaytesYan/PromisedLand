#pragma once

#include "../GameObject.hpp"
#include "../Resources.hpp"

class Cell : GameObject 
{
public:
    virtual Resources getAppearIncome() 
    {
        return kStartResources;
    }

    virtual Resources getTickIncome()
    {
        return kStartResources;
    }
};