#pragma once

#include "IncodeOutcome.h"

#include "../Field.h"
#include "../../Resources.h"

class Building : public Field
{
public:
    Building(int x, int y) : Field(x, y)
    { }

    virtual Resources getBuildingIncome() = 0;
    virtual Resources getTickIncome()     = 0;

    bool onClick(int x, int y) override {}
    void onTick()              override {}
};
