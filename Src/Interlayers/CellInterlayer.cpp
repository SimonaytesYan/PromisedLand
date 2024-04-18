#include "CellInterlayer.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Graphics/Widget/Window.hpp"

void CellInterlayer::pushToView(const EventPtr event)
{
    cell_view_group->push(event);
}

void CellInterlayer::pushToLogic(const EventPtr event)
{
    switch (event->event_type)
    {
    case EventType::TICK:
        cell_manager.onTick();
        break;
    case EventType::MOUSE_CLICK:
        {
        const MouseEvent* mouse_event = static_cast<const MouseEvent*>(event.get());
        cell_manager.createCell(mouse_event->pos);
        break;
        }
    case EventType::DESTROY_CELL_EVENT:
        break;
    case EventType::NEW_CITIZEN_EVENT:
        
        break;
    default:
        break;
    }
}