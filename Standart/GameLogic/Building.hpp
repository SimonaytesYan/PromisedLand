#pragma once

#include "Cell.hpp"
#include "../Utils/Bitmask.hpp"

class Building : public Cell 
{
public:

    static Bitmask   getBuildMask(size_t field_type);
    static Resources getAppearIncome(size_t field_type);

    explicit Building(const size_t _field_type, const long int _max_workers = 0)
      :  Cell        (_field_type),
         max_workers (_max_workers),
         cur_workers (0)
    {}

    virtual Resources getAppearIncome() const
    { return kZeroResources; }

    virtual Resources getTickIncome()
    { return kZeroResources; }

    virtual Resources getDestroyIncome() const
    { return kZeroResources; }

    // 1 in n-th bit if this Building could    be build on the n-th FieldType
    // 0 in n-th bit if this Building couldn`t be build on the n-th FieldType
    virtual Bitmask getBuildMask() const
    { return kMaxBitmask; }

    virtual long int getMaxWorkers() const
    {
        return max_workers;
    }

    virtual long int getCurWorkers() const
    {
        return cur_workers;
    }

    virtual void setCurWorkers(long int _cur_workers)
    {
        cur_workers = _cur_workers;
    }

    virtual void setPopulation(long int new_pop)
    {}

private:
    long int max_workers;
    long int cur_workers;
};