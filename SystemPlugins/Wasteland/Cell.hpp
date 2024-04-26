#pragma once

#include "../../Standart/GameLogic/Building.hpp"

static const Resources kAppearIncome  = Resources(0, 0, 0, 0, 0, 0);
static const Resources kTickIncome    = Resources(0, 0, 0, 0, 0, 0);
static const Resources kDestroyIncome = Resources(0, 0, 0, 0, 0, 0);
static const Bitmask   kBuildMask     = ~(0);

class WastelandCell : public Building
{
public:
    explicit WastelandCell();

    Resources getAppearIncome() const override;
    Resources getTickIncome() override;
    Resources getDestroyIncome() const override;
    Bitmask   getBuildMask() const override;
};