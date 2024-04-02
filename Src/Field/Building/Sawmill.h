#pragma once

#include "Building.h"

class Sawmill : public Building
{
public:
    Sawmill(int x, int y) : Building(x, y)
    { }

    Resources getBuildingIncome() override 
    { return SAWMILL_BUILDING; }

    Resources getTickIncome() override 
    { return SAWMILL_TICK; }
 
    void draw(RenderTarget& render_target) override
    {
        render_target.drawCircle(x, y, kFieldSize, kBackgroundColor);
    }

private:
    const sf::Color kBackgroundColor = sf::Color(124, 252, 0);
};
