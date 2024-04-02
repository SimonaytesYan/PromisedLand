#pragma once

#include "IncodeOutcome.h"

#include "Field.h"
#include "Resources.h"

class Building : public Field
{
public:
    virtual Resources getBuildingIncome();
    virtual Resources getTickIncome();
};
