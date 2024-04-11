#include "CellInterlayer.hpp"
#include "../Graphics/Widget/Window.hpp"

void CellInterlayer::pushToView(const Event* event)
{
    switch (event->event_type)
    {
    case EventType::BUILD_CELL_EVENT:
      {
        const BuildCellEvent* build_event = static_cast<const BuildCellEvent*>(event);
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

void CellInterlayer::pushToLogic(const Event* event)
{
    switch (event->event_type)
    {
    case EventType::TICK:
        cell_manager.onTick();
        break;
    case EventType::MOUSE_CLICK:
        {
        const MouseEvent* mouse_event = static_cast<const MouseEvent*>(event);
        cell_manager.createCell(mouse_event->pos);
        break;
        }
    case EventType::DESTROY_CELL_EVENT:
        {
        const DestroyCellEvent* delete_event = static_cast<const DestroyCellEvent*>(event);
        int delete_ind = -1;

        for (size_t i = 0; i < cell_views.size(); ++i)
        {
            if (cell_views[i] == delete_event->cell_view)
            {
                delete_ind = i;
                break;
            }
        }

        if (delete_ind != -1)
        {
            cell_manager.deleteCell(delete_ind);
            cell_views.erase(cell_views.begin() + delete_ind);
        }

        window->push(delete_event);

        break;
        }
    default:
        break;
    }
}