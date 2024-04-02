#pragma once

#include "Building.h"

class Well : public Building
{
public:
    Well(int x, int y) : Building(x, y)
    { }

    Resources getBuildingIncome() override 
    { return WELL_BUILDING; }

    Resources getTickIncome() override 
    { return WELL_TICK; }
 
    void draw(RenderTarget& render_target) override
    {
        static Texture texture(kTexturePath);
        render_target.drawTexture(x, y, texture);
    }

private:
    const char* kTexturePath = "Assets/well.png";

private:
    const sf::Color kBackgroundColor = sf::Color(73, 126, 118);
};
