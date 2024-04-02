#pragma once

#include "../GameObject.h"
#include "../StlVector/Src/Vector.hpp"
#include "Button.h"
#include "BuildingManager.h"

struct ButtonArgs
{
    BuildMenu* build_menu;
    Building*  building;
};

class BuildMenu : public GameObject
{
public:
    BuildMenu(int x, int y, BuildingManager& build_manager) :
    GameObject   (x, y),
    build_manager(build_manager)
    { }
    
    void setBuildingType(Building* building)
    {
        build_manager.setBuildingType(building);
    }

    void draw(RenderTarget& render_target) override
    {
        const size_t size = menu.Size();
        for (size_t i = 0; i < size; i++)
            menu[i].draw(render_target);
    }

    bool onClick(int x, int y) override
    {
        const size_t size = menu.Size();
        for (size_t i = 0; i < size; i++)
            if (menu[i].onClick(x, y))
                return true;
        return false;
            
    }
    void onTick() override
    { }

private:
    BuildingManager& build_manager;
    Vector<Button> menu;
};

void SetBuildingType(void* arg)
{
    ButtonArgs* button_args = static_cast<ButtonArgs*>(arg);
    button_args->build_menu->setBuildingType(button_args->building);
}
