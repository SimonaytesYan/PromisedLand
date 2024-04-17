#include "CellInterlayer.hpp"
#include "../Graphics/Widget/Window.hpp"

void CellInterlayer::pushToView(const EventPtr event)
{
    switch (event->event_type)
    {
    case EventType::BUILD_CELL_EVENT:
      {
        const BuildCellEvent* build_event = static_cast<const BuildCellEvent*>(event.get());
        cell_views.push_back(build_event->cell_view);
        break;
      }
    
    default:
        break;
    }

    const size_t cell_views_size = cell_views.size();
    for (size_t i = 0; i < cell_views_size; i++)
        cell_views[i]->push(event);
    window->push(event);
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
        {
        const DestroyCellEvent* delete_event = static_cast<const DestroyCellEvent*>(event.get());

        for (size_t i = 0; i < cell_views.size(); ++i)
        {
            if (cell_views[i] == delete_event->cell_view)
            {
                cell_manager.deleteCell(i);
                cell_views.erase(cell_views.begin() + i);
                break;
            }
        }

        window->push(event);

        break;
        }
    case EventType::NEW_CITIZEN_EVENT:
        
        break;
    default:
        break;
    }
}