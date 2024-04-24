#pragma once

#include "../../Standart/GameLogic/Building.hpp"

class HouseCell : public Building
{
public:
    explicit HouseCell();

    Resources getAppearIncome() const override;
    Resources getTickIncome() const override;
    Resources getDestroyIncome() const override;
    Bitmask   getBuildMask() const override;
};