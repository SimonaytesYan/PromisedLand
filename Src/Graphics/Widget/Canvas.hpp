#pragma once

#include "../../Utils/RenderTarget.hpp"
#include "Widget.hpp"

class Canvas : public Widget
{
public:
    explicit Canvas(const Point _pos, 
                    const size_t _host_size_x, 
                    const size_t _host_size_y, 
                    const size_t _canvas_size_x, 
                    const size_t _canvas_size_y)
      : Widget            (0, 0),
        original_host_pos (_pos),
        relative_host_pos (_pos),
        host_size_x       (_host_size_x),
        host_size_y       (_host_size_y),
        canvas_size_x     (_canvas_size_x),
        canvas_size_y     (_canvas_size_y),
        canvas_renderer   (new RenderTarget({_canvas_size_x, _canvas_size_y}))
    {}

    // Non-copyable
    Canvas          (const Canvas& other) = delete;
    Canvas operator=(const Canvas& other) = delete;

    // Non-movable
    Canvas          (Canvas&& other) = delete;
    Canvas operator=(Canvas&& other) = delete;

    ~Canvas()
    {
        delete canvas_renderer;
    }

    void draw(RenderTargetI& render_target) override
    {
        canvas_renderer->display();

        TextureI* texture = canvas_renderer->getTexture();
        render_target.drawTexture(original_host_pos, relative_host_pos, host_size_x, host_size_y, *texture);

        delete texture;
    }

    void push(const EventPtr event) override
    {}

    void updateHostPosition(const int dx, const int dy)
    {
        relative_host_pos.x = 
            std::max(std::min(relative_host_pos.x + dx, original_host_pos.x + canvas_size_x - host_size_x), original_host_pos.x);
        relative_host_pos.y = 
            std::max(std::min(relative_host_pos.y + dy, original_host_pos.y + canvas_size_y - host_size_y), original_host_pos.y);
    }

    RenderTarget& getRenderTarget()
    {
        return *canvas_renderer;
    }

    Point getRelativePos(const Point absolute_pos)
    {
        return {absolute_pos.x + relative_host_pos.x, absolute_pos.y + relative_host_pos.y};
    }

    bool isPointVisible(const Point absolute_pos)
    {
        return absolute_pos.x >= original_host_pos.x                &&
               absolute_pos.x <= original_host_pos.x + host_size_x  &&
               absolute_pos.y >= original_host_pos.y                &&
               absolute_pos.y <= original_host_pos.y + host_size_y;
    }

    bool isCellVisible(const Point absolute_pos)
    {
        return absolute_pos.x >= relative_host_pos.x                &&
               absolute_pos.x <= relative_host_pos.x + host_size_x  &&
               absolute_pos.y >= relative_host_pos.y                &&
               absolute_pos.y <= relative_host_pos.y + host_size_y;
    }

private:
    Point original_host_pos;
    Point relative_host_pos;

    size_t host_size_x;
    size_t host_size_y;

    size_t canvas_size_x;
    size_t canvas_size_y;

    RenderTarget* canvas_renderer;
};