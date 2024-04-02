#pragma once

#include "Building.h"

class Well : public Building
{
public:
    Resources getBuildingIncome() override 
    { return WELL_BUILDING; }

    Resources getTickIncome() override 
    { return WELL_TICK; }
 
    void draw(RenderTarget& render_target) override
    {
        render_target.drawCircle(x, y, kFieldSize, kFieldSize, kBackgroundColor);
    }

private:
    const sf::Color kBackgroundColor = sf::Color(73, 126, 118);
};