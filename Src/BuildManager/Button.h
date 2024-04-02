#pragma once

#include "../GameObject.h"

class Button : GameObject
{
    
    void draw(RenderTarget& render_target) override;
    bool onClick(int x, int y) override;
    void onTick() override;
};
