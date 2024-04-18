#include "CellView.hpp"
#include "../Widget/CellViewGroup.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

void CellView::push(const EventPtr event)
{ 
    switch (event->event_type)
    {
    case EventType::MOUSE_CLICK:
        {
        const MouseEvent* mouse_event = static_cast<const MouseEvent*>(event.get());
        onClick(mouse_event->pos, event);
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
        parent.push(delete_event);
        parent.pushToLogic(delete_event);

        MouseEvent* mouse_event = new MouseEvent(pos);
        parent.pushToLogic(mouse_event);
    }
}