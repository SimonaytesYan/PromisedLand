#include "MapWidget.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

void MapWidget::push(const EventPtr event)
{
    switch (event->event_type)
    {
    case EventType::SMALL_MAP_CHANGED:
        {
        const SmallMapChangedEvent* map_event = static_cast<const SmallMapChangedEvent*>(event.get());
        const Color pixel_color = getTextureMeanColor(CellKeeper::getAsset(map_event->field_type));
        const Point pixel_pos   = {map_event->pos.x / kCellSize, map_event->pos.y / kCellSize};

        for (int i = 0; i < scale; ++i) 
        {
            for (int j = 0; j < scale; ++j)
            {
                pixel_texture->setPixel({scale * pixel_pos.x + i, scale * pixel_pos.y + j}, pixel_color);
            }
        }

        break;
        }
    case EventType::SMALL_MAP_MOVED:
        {
        const SmallMapMovedEvent* move_event = static_cast<const SmallMapMovedEvent*>(event.get());
        cur_frame_pos = move_event->new_pos;

        break;
        }
    case EventType::CLICKED_MOUSE_MOVED:
        {
        const ClickedMouseMoveEvent* mouse_event = static_cast<const ClickedMouseMoveEvent*>(event.get());
        if (!isMouseInFrame(mouse_event->new_pos)) break;

        if (cell_interlayer)
        {
            const int real_delta_x = -1 * mouse_event->delta_x * kCellSize / scale;
            const int real_delta_y = -1 * mouse_event->delta_y * kCellSize / scale;
            cell_interlayer->pushToView(new MapMovedEvent(real_delta_x, real_delta_y));
        }

        break;
        }
    default:
        break;
    }
}