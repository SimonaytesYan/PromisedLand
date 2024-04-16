#pragma once

#include "Cell.hpp"

class Building : public Cell 
{
public:

    explicit Building(const long int _max_workers = 0)
      :  Cell        (),
         max_workers (_max_workers),
         cur_workers (0)
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

private:
    long int max_workers;
    long int cur_workers;
};