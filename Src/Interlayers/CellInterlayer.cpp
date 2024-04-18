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
            const MouseClickEvent* mouse_event = static_cast<const MouseClickEvent*>(event.get());
            cell_manager.createCell(mouse_event->pos);
            cell_view_group->addCell(cell_manager.cell_type, mouse_event->pos);
            break;
        }
        case EventType::DESTROY_CELL_LOGIC_EVENT:
        {
            const DestroyCellLogicEvent* dest_event = static_cast<const DestroyCellLogicEvent*>(event.get());
            cell_manager.deleteCell(dest_event->index_in_vector);
            break;
        }
        case EventType::NEW_CITIZEN_EVENT:
            break;
        default:
            break;
    }
}

void CellInterlayer::createCell(const FieldType filed_type, const Point pos)
{
    cell_manager.setCellType(filed_type);
    cell_manager.createCell(pos);
    cell_view_group->addCell(filed_type, pos);
}