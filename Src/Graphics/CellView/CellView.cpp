#include "CellView.hpp"
#include "../Widget/CellViewGroup.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

Color CellView::kChosenCellColor = {255, 255, 255, 128};

#define CELL_LOGIC(name)  \
    case FieldType::name:                       \
        return new name##View(pos, cell_view_group);

#define BUILDING_LOGIC(name, ...) CELL_LOGIC(name)

CellView* CellView::createInstance(const FieldType field_type, const Point pos, 
                                   CellViewGroup& cell_view_group)
{
    switch (field_type)
    {
        #include "../../GameLogic/Tiles/CellPreforms.hpp"
        #include "../../GameLogic/Tiles/BuildingPreforms.hpp"

        default:
            return nullptr;
    }
}

#undef CELL_LOGIC
#undef BUILDING_LOGIC

void CellView::push(const EventPtr event)
{ 
    switch (event->event_type)
    {
    case EventType::MOUSE_CLICK:
      {
        const MouseClickEvent* mouse_event = static_cast<const MouseClickEvent*>(event.get());
        onClick(mouse_event->pos, event);
        break;
      }
    case EventType::MOUSE_MOVE:
      {
        const MouseMoveEvent* mouse_event = static_cast<const MouseMoveEvent*>(event.get());
        onMouseMove(mouse_event->pos);
        break;
      }
    default:
        break;
    }
}

void CellView::onClick(const Point point, const EventPtr event)
{
    // printf("CellView::onClick(%d %d)\n", pos.x, pos.y);
    if (pos.x < point.x && point.x < pos.x + kFieldSize &&
        pos.y < point.y && point.y < pos.y + kFieldSize)
    {
        parent.pushToLogic(new TryBuildEvent(index_in_cell_group, pos));
    }
}

void CellView::onMouseMove(const Point point)
{
    if (pos.x < point.x && point.x < pos.x + kFieldSize &&
        pos.y < point.y && point.y < pos.y + kFieldSize)
    {
        is_chosen = true;
    }
    else
    {
        is_chosen = false;
    }
}
