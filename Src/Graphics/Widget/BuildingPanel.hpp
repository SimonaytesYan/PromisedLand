#pragma once

#include "Widget.hpp"
#include "Button.hpp"
#include "../CellView/CellView.hpp"
#include "../../../StlVector/Src/Vector.hpp"
#include "../../Interlayers/BuldingPanelInterlayer.hpp"
#include "../../Utils/Functor.hpp"
#include "../../CellLoader/CellKeeper.hpp"

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
        std::vector<CellInterface*> building_interfaces;
        CellKeeper::getBuildings(building_interfaces);

        size_t build_cnt = 0;
        for (const auto building_int : building_interfaces)
        {
            ButtonArgs    args = ButtonArgs(*this, static_cast<FieldType>(building_int->getId()));
            BasicFunctor* func = new Functor<ButtonArgs>(SetFieldType, args);

            buttons.EmplaceBack(Point(pos.x, pos.y + 70 * build_cnt), kCellSize, kCellSize, 
                                    func, building_int->getAsset());

            build_cnt++;
        }
    }
    
    void draw(RenderTarget& render_target) override
    {
        const size_t size = buttons.Size();
        for (size_t i = 0; i < size; i++)
            buttons[i].draw(render_target);
    }

    void push(const EventPtr event)
    {
        switch (event->event_type)
        {
            case EventType::MOUSE_RELEASE:
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

void SetFieldType(ButtonArgs arg)
{
    arg.build_menu.setFieldType(arg.field);
}
