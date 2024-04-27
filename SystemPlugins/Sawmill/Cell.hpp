#pragma once

#include "../../Standart/GameLogic/Building.hpp"

static const Resources kAppearIncome  = Resources( 0,  0, -10, 0, 0, 0);
static const Resources kTickIncome    = Resources( 0,  0,   5, 0, 0, 0);
static const Resources kDestroyIncome = Resources( 0,  0,   7, 0, 0, 0);
static const Bitmask   kBuildMask     = ~((1 << 0) | (1 << 1) | (1 << 3));

class SawmillCell : public Building
{
public:
    explicit SawmillCell();

    Resources getAppearIncome() const override;
    Resources getTickIncome() override;
    Resources getDestroyIncome() const override;
    Bitmask   getBuildMask() const override;
};