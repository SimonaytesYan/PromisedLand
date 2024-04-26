#include "CellInterlayer.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Events/Events.hpp"

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
        case EventType::TRY_BUILD_EVENT:
        {
            const TryBuildEvent* try_build_event = static_cast<const TryBuildEvent*>(event.get());
            cell_manager.tryBuildCell(try_build_event->index, try_build_event->position);
            break;
        }
        case EventType::DESTROY_CELL_LOGIC_EVENT:
        {
            const DestroyCellLogicEvent* dest_event = static_cast<const DestroyCellLogicEvent*>(event.get());
            cell_manager.deleteCell(dest_event->index_in_vector);
            break;
        }
        case EventType::NEW_CITIZEN_EVENT:
        {
            const NewCitizensEvent* new_cit_event = static_cast<const NewCitizensEvent*>(event.get());
            cell_manager.onNewCitizenArrival(new_cit_event->citizens);
            break;
        }
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