#pragma once

#include "Building.h"

class Windmill : public Building
{
public:
    Resources getBuildingIncome() override 
    { return WINDMILL_BUILDING; }

    Resources getTickIncome() override 
    { return WINDMILL_TICK; }
 
    void draw(RenderTarget& render_target) override
    {
        render_target.drawCircle(x, y, kFieldSize, kBackgroundColor);
    }

private:
    const sf::Color kBackgroundColor = sf::Color(188, 93, 88);
};