#pragma once

#include "Cell.hpp"

class Building : public Cell 
{
public:

    explicit Building()
      :  Cell()
    {}

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