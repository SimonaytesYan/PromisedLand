#include "CellView.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

void CellView::push(const Event* event)
{ 
    switch (event->event_type)
    {
    case EventType::MOUSE_CLICK:
        {
        const MouseEvent* mouse_event = static_cast<const MouseEvent*>(event);
        onClick(mouse_event->pos, event);
        break;
        }
    
    default:
        break;
    }
}

void CellView::onClick(const Point point, const Event* event)
{
    // printf("CellView::onClick(%d %d)\n", pos.x, pos.y);
    if (pos.x < point.x && point.x < pos.x + kFieldSize &&
        pos.y < point.y && point.y < pos.y + kFieldSize)
    {
        MouseEvent mouse_event(pos);
        interlayer.pushToLogic(&mouse_event);

        DestroyCellEvent delete_event(this);
        interlayer.pushToLogic(&delete_event);
    }
}