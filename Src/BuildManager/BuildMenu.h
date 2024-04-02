#pragma once

#include "../GameObject.h"
#include "../StlVector/Src/Vector.hpp"
#include "Button.h"
#include "BuildingManager.h"
#include "../Field/Fields.h"

struct ButtonArgs
{
    ButtonArgs(BuildMenu* build_menu, FieldType field) :
    build_menu (build_menu),
    field      (field)
    { }

    BuildMenu* build_menu;
    FieldType  field;
};

class BuildMenu : public GameObject
{
public:
    BuildMenu(int x, int y, BuildingManager& build_manager) :
    GameObject   (x, y),
    build_manager(build_manager)
    {
        const size_t field_num = static_cast<size_t>(FieldType::FieldNumber);
        for (size_t i = 0; i < field_num; i++)
        {
            Functor func(SetFieldType, 
                        new ButtonArgs(this, static_cast<FieldType>(i)));

            menu.PushBack(Button(x, y + 70 * i, kFieldSize, kFieldSize, 
                                 func, kFieldsAssets[i]));
        }
    }
    
    void setFieldType(FieldType building)
    {
        build_manager.setFieldType(building);
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

void SetFieldType(void* arg)
{
    ButtonArgs* button_args = static_cast<ButtonArgs*>(arg);
    button_args->build_menu->setFieldType(button_args->field);
}
