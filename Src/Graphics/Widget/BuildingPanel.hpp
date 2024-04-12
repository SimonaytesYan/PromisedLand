#pragma once

#include "Widget.hpp"
#include "Button.hpp"
#include "../CellView/CellViewCreator.hpp"
#include "../../../StlVector/Src/Vector.hpp"
#include "../../Interlayers/BuldingPanelInterlayer.hpp"
#include "../../Utils/Functor.hpp"

class BuildingPanel;

struct ButtonArgs
{
    ButtonArgs(BuildingPanel& build_menu, const FieldType field) :
    build_menu (build_menu),
    field      (field)
    { }

    BuildingPanel&  build_menu;
    const FieldType field;
};

void SetFieldType(ButtonArgs arg);

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
            ButtonArgs    args = ButtonArgs(*this, static_cast<FieldType>(i));
            BasicFunctor* func = new Functor<ButtonArgs>(SetFieldType, args);

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
        SelectBuildingEvent select_build_event(field_type);
        interlayer.pushToLogic(&select_build_event);
    }

private:
    Vector<Button>           buttons;
    BuildingPanelInterlayer& interlayer;
};

void SetFieldType(ButtonArgs arg)
{
    arg.build_menu.setFieldType(arg.field);
}
