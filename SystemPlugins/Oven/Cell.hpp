#pragma once

#include "../../Standart/GameLogic/Building.hpp"

static const Resources kAppearIncome  = Resources( 0,  0,   0, 0, 0, -30);
static const Resources kTickIncome    = Resources(25,  0,  0, 0, 0,  0 );
static const Resources kDestroyIncome = Resources( 0,  0,   0, 0, 0,  20);
static const Bitmask   kBuildMask     = ~((1 << 1) | (1 << 2) | (1 << 3));

class OvenCell : public Building
{
public:
    explicit OvenCell();

    Resources getAppearIncome() const override;
    Resources getTickIncome() override;
    Resources getDestroyIncome() const override;
    Bitmask   getBuildMask() const override;
};