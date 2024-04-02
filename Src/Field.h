#pragma once

#include "GameObject.h"

class Field : public GameObject
{
    void draw(RenderTarget& render_target) override; 
    void onClick(int x, int y) override;
    void onTick() override;
};


