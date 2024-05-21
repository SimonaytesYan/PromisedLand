#pragma once

#include <vector>

#include "../../CellLoader/CellKeeper.hpp"
#include "Widget.hpp"

class MapWidget : public Widget 
{
public:

    explicit MapWidget(const Point pos, const size_t size_x, const size_t size_y, const int scale)
      : Widget        (pos),
        size_x        (size_x),
        size_y        (size_y),
        scale         (scale),
        pixels        (size_x * size_y, Color::Transparent),
        pixel_texture (new RenderTarget({size_x, size_y}))
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
        default:
            break;
        }
    }

private:
    const size_t size_x;
    const size_t size_y;
    const int    scale;

    std::vector<Color> pixels;
    RenderTarget*      pixel_texture;
};