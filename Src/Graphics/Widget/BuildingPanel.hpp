#pragma once

#include "Widget.hpp"
#include "Button.hpp"
#include "../CellView/CellViewCreator.hpp"
#include "../../../StlVector/Src/Vector.hpp"
#include "../../Interlayers/BuldingPanelInterlayer.hpp"

class BuildingPanel;
void SetFieldType(void* arg);

struct ButtonArgs
{
    ButtonArgs(BuildingPanel* build_menu, FieldType field) :
    build_menu (build_menu),
    field      (field)
    { }

    BuildingPanel* build_menu;
    FieldType      field;
};

class BuildingPanel : public Widget
{
public:
    BuildingPanel(Point pos, BuildingPanelInterlayer& interlayer) : 
    Widget     (pos),
    interlayer (interlayer)
    {
        const size_t field_num = static_cast<size_t>(FieldType::FieldNumber);
        for (size_t i = 0; i < field_num; i++)
        {
            Functor func(SetFieldType, 
                        new ButtonArgs(this, static_cast<FieldType>(i)));

            buttons.PushBack(Button(Point(pos.x, pos.y + 70 * i), kFieldSize, kFieldSize, 
                                    func, kCellsAssets[i]));
        }
    }
    
    void draw(RenderTarget& render_target) override
    {
        const size_t size = buttons.Size();
        for (size_t i = 0; i < size; i++)
            buttons[i].draw(render_target);
    }

    void push(const Event* event)
    {
        switch (event->event_type)
        {
            case EventType::MOUSE_CLICK:
            {
                const size_t size = buttons.Size();
                    for (size_t i = 0; i < buttons.Size(); i++)
                        buttons[i].push(event);
                break;
            }
            default:
                break;
        }
    }

    void setFieldType(const FieldType field_type)
    {
        interlayer.pushToLogic(new SelectBuildingEvent(field_type));
    }

private:
    Vector<Button>           buttons;
    BuildingPanelInterlayer& interlayer;
};

void SetFieldType(void* arg)
{
    ButtonArgs* button_args = static_cast<ButtonArgs*>(arg);
    button_args->build_menu->setFieldType(button_args->field);
}
