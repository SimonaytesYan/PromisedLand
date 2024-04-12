#pragma once

#include "../GameObject.hpp"
#include "../Resources.hpp"

class Cell : GameObject 
{
public:
    virtual Resources getAppearIncome() const
    {
        return kZeroResources;
    }

    virtual Resources getTickIncome() const
    {
        return kZeroResources;
    }

    virtual Resources getDestroyIncome() const
    {
        return kZeroResources;
    }
};