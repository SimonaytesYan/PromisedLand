#pragma once

#include "Field.h"
#include "Resources.h"

class ResourcesManager;

class Building : public Field
{
public:
    virtual Resources getBuildingIncome();
    virtual Resources getTickIncome();

};
