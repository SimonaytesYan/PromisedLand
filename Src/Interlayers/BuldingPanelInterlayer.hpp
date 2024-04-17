#pragma once

#include "ViewInterlayer.hpp"
#include "../Managers/CellManager.hpp"

class BuildingPanelInterlayer : ViewInterlayer
{
public:
    BuildingPanelInterlayer(CellManager& cell_manager) :
    cell_manager (cell_manager)
    {}

    void pushToLogic(const EventPtr event) override
    {
        const SelectBuildingEvent* select_event = static_cast<const SelectBuildingEvent*>(event.get());

        switch (select_event->event_type)
        {
        case EventType::SELECT_BUILDING_EVENT:
            cell_manager.setCellType(select_event->type);
            break;
        case EventType::TICK:
        case EventType::MOUSE_CLICK:
        case EventType::RESOURCES_CHANGED_EVENT:
            break;
        default:
            break;
        }
    }

private:
    CellManager& cell_manager;
};