#pragma once

#include "Building.h"

class House : public Building
{
public:
    House(int x, int y) : Building(x, y)
    { }

    Resources getBuildingIncome() override 
    { return HOUSE_BUILDING; }

    Resources getTickIncome() override 
    { return HOUSE_TICK; }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawCircle(x, y, kFieldSize, kBackgroundColor);
    }

private:
    const sf::Color kBackgroundColor = sf::Color(111, 79, 40);
};
