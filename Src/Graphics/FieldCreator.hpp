#pragma once

#include "Resources.h"

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

    bool onClick(int click_x, int click_y) override 
    {
        return (x <= click_x) && (click_x <= (x + kFieldSize)) &&
               (y <= click_y) && (click_y <= (y + kFieldSize));
    }

    virtual Resources getAppearIncome() = 0;
    virtual Resources getTickIncome()     = 0;

    void onTick() override {}

private:
    const char* kTexturePath = "Assets/field.png";
};
