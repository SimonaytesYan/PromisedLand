#pragma once

#include "../../Utils/RenderTarget.hpp"
#include "Widget.hpp"

class Canvas : public Widget
{
public:
    explicit Canvas(const Point _pos, const size_t _size_x, const size_t _size_y)
      : Widget          (_pos),
        host_pos        (),
        host_size_x     (),
        host_size_y     (),
        canvas_renderer (new RenderTarget({_size_x, _size_y}))
    {}

    explicit Canvas(const size_t _size_x, const size_t _size_y)
      : Widget          (0, 0),
        host_pos        (),
        host_size_x     (),
        host_size_y     (),
        canvas_renderer (new RenderTarget({_size_x, _size_y}))
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
        render_target.drawTexture(host_pos, host_size_x, host_size_y, *canvas_renderer->getTexture());
    }

    void push(const EventPtr event) override
    {

    }

private:
    const Point host_pos;

    const size_t host_size_x;
    const size_t host_size_y;

    RenderTarget* canvas_renderer;
};