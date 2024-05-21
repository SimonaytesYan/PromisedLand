#pragma once

#include <vector>

#include "../../CellLoader/CellKeeper.hpp"
#include "Widget.hpp"

class MapWidget : public Widget 
{
public:

    explicit MapWidget(const Point pos, 
                       const size_t size_x, 
                       const size_t size_y, 
                       const int scale, 
                       const size_t frame_size_x, 
                       const size_t frame_size_y)
      : Widget        (pos),
        size_x        (size_x),
        size_y        (size_y),
        scale         (scale),
        cur_frame_pos (0, 0),
        frame_size_x  (frame_size_x),
        frame_size_y  (frame_size_y),
        pixels        (size_x * size_y, Color::Transparent),
        pixel_texture (new RenderTarget({size_x, size_y})),
        is_moving     (false),
        last_pos      ()
    {}

    // Non-copyable
    MapWidget          (const MapWidget& other) = delete;
    MapWidget operator=(const MapWidget& other) = delete;

    // Non-movable
    MapWidget          (MapWidget&& other) = delete;
    MapWidget operator=(MapWidget&& other) = delete;

    ~MapWidget()
    {
        delete pixel_texture;
    }

    void draw(RenderTarget& render_target) override
    {
        pixel_texture->display();

        Texture* texture = pixel_texture->getTexture();
        render_target.drawTexture(pos, *texture);

        delete texture;

        render_target.drawRect({pos.x + scale * cur_frame_pos.x / kCellSize, pos.y + scale * cur_frame_pos.y / kCellSize}, 
                               {scale * frame_size_x / kCellSize, scale * frame_size_y / kCellSize}, 
                               kFrameColor,
                               kFrameBorderSize,
                               kFrameBorderColor);
    }

    void push(const EventPtr event) override
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
        case EventType::MOUSE_CLICK:
          {
            const MouseClickEvent* click_event = static_cast<const MouseClickEvent*>(event.get());
            if (isMouseInFrame(click_event->pos)) 
            {
                // is_moving = true;
                // last_pos  = 
            }

            break;
          }
        default:
            break;
        }
    }

private:

    bool isMouseInFrame(const Point mouse_pos) 
    {
        const Point frame_start = {pos.x + scale * cur_frame_pos.x / kCellSize, pos.y + scale * cur_frame_pos.y / kCellSize};
        const Point frame_size  = {scale * frame_size_x / kCellSize, scale * frame_size_y / kCellSize};

        return mouse_pos.x >= frame_start.x                &&
               mouse_pos.x <= frame_start.x + frame_size.x &&
               mouse_pos.y >= frame_start.y                &&
               mouse_pos.y <= frame_start.y + frame_size.y; 
    }

private:
    const Color kFrameColor       = {255, 255, 255, 128};
    const Color kFrameBorderColor = {255, 255, 255, 200};
    const int   kFrameBorderSize  = 2;

private:
    const size_t size_x;
    const size_t size_y;
    const int    scale;

    Point        cur_frame_pos;
    const size_t frame_size_x;
    const size_t frame_size_y;

    std::vector<Color> pixels;
    RenderTarget*      pixel_texture;

    bool  is_moving;
    Point last_pos;
};