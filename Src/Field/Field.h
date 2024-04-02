#pragma once

#include "../GameObject.h"

const size_t kFieldSize = 64;

class Field : public GameObject
{
public:
    Field(int x, int y) : GameObject(x, y)
    { }

    void draw(RenderTarget& render_target) override
    {
        static Texture texture(kTexturePath);
        render_target.drawTexture(x, y, texture);
    }

    bool onClick(int x, int y) override {}
    void onTick()              override {}

private:
    const char* kTexturePath = "Assets/field.png";

private:
    const sf::Color kBackgroundColor = sf::Color::Green;
};
