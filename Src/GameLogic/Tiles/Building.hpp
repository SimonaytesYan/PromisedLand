#pragma once

#include "Cell.hpp"
#include "../../Utils/Bitmask.hpp"

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

    // 1 in n-th bit if this Building could    be build on the n-th FieldType
    // 0 in n-th bit if this Building couldn`t be build on the n-th FieldType
    virtual Bitmask getBuildMask() const
    { return kMaxBitmask; }

private:
    long int max_workers;
    long int cur_workers;
};