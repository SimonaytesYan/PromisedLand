#include "CellView.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

Color CellView::kChosenCellColor = {255, 255, 255, 128};

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
        DestroyCellEvent* delete_event = new DestroyCellEvent(this);
        interlayer.pushToLogic(delete_event);

        MouseClickEvent* mouse_event = new MouseClickEvent(pos);
        interlayer.pushToLogic(mouse_event);
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