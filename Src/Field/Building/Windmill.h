#pragma once

#include "Building.h"

class Windmill : public Building
{
public:
    Windmill(int x, int y) : Building(x, y)
    { }

    Resources getBuildingIncome() override 
    { return WINDMILL_BUILDING; }

    Resources getTickIncome() override 
    { return WINDMILL_TICK; }
 
    void draw(RenderTarget& render_target) override
    {
        static Texture texture(kTexturePath);
        render_target.drawTexture(x, y, texture);
    }

private:
    const char* kTexturePath = "Assets/windmill.png";

private:
    const sf::Color kBackgroundColor = sf::Color(188, 93, 88);
};