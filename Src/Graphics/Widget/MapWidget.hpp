#pragma once

#include <vector>

#include "Widget.hpp"

class MapWidget : public Widget 
{
public:

    explicit MapWidget(const Point pos, const size_t size_x, const size_t size_y)
      : Widget        (pos),
        size_x        (size_x),
        size_y        (size_y),
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

    }

    void push(const EventPtr event) override
    {

    }

private:
    const size_t size_x;
    const size_t size_y;

    std::vector<Color> pixels;
    RenderTarget*      pixel_texture;
};