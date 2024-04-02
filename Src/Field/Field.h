#pragma once

#include "../GameObject.h"

const size_t kFieldSize = 32;

class Field : public GameObject
{
public:
    Field(int x, int y) : GameObject(x, y)
    { }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawCircle(x, y, kFieldSize, kBackgroundColor);
    }

    void onClick(int x, int y) override {}
    void onTick()              override {}

private:
    const sf::Color kBackgroundColor = sf::Color::Green;
};
