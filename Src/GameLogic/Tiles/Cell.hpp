#pragma once

#include "../GameObject.hpp"
#include "../Resources.hpp"

class Cell : GameObject 
{
public:
    virtual Resources getAppearIncome() const
    {
        return kStartResources;
    }

    virtual Resources getTickIncome() const
    {
        return kStartResources;
    }
};