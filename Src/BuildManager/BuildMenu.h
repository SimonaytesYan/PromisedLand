#pragma once

#include "../GameObject.h"
#include "../StlVector/Src/Vector.hpp"
#include "Button.h"

class BuildManager;

class BuildMenu : public GameObject
{
public:
    void draw(RenderTarget& render_target) override;
    bool onClick(int x, int y) override;
    void onTick() override;

private:
    BuildManager& build_manager;
    Vector<Button> menu;
};
