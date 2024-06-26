#pragma once

#include "../../Standart/GameLogic/Building.hpp"

static const Resources kAppearIncome  = Resources( 0,  0, -15,  5,  5, 0);
static const Resources kTickIncome    = Resources(-5, -5,   0,  0,  0, 0);
static const Resources kDestroyIncome = Resources( 0,  0,  10, -5, -5, 0);
static const Bitmask   kBuildMask     = ~((1 << 1) | (1 << 2) | (1 << 3));

class HouseCell : public Building
{
public:
    explicit HouseCell();

    Resources getAppearIncome() const override;
    Resources getTickIncome() override;
    Resources getDestroyIncome() const override;
    Bitmask   getBuildMask() const override;

    void setPopulation(long int new_pop) override
    {
        cur_citizens = new_pop;
    }

private:
    static const unsigned kBirthTicks  = 20;
    static const unsigned kRandomCoeff = 4;

    long int tick_count;
    long int cur_citizens;
};