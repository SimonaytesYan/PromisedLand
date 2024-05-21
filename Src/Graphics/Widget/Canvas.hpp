#pragma once

#include "../../Utils/RenderTarget.hpp"
// #include "../CellView/CellView.hpp"
#include "Widget.hpp"

class Canvas : public Widget
{
public:
    explicit Canvas(const Point _pos, 
                    const size_t _host_size_x, 
                    const size_t _host_size_y, 
                    const size_t _canvas_size_x, 
                    const size_t _canvas_size_y,
                    const Point  _inv_area_pos    = {0, 0},
                    const size_t _inv_area_size_x = 0,
                    const size_t _inv_area_size_y = 0)
      : Widget            (0, 0),
        original_host_pos (_pos),
        relative_host_pos (_pos),
        host_size_x       (_host_size_x),
        host_size_y       (_host_size_y),
        canvas_size_x     (_canvas_size_x),
        canvas_size_y     (_canvas_size_y),
        canvas_renderer   (new RenderTarget({_canvas_size_x, _canvas_size_y})),
        inv_area_pos      (_inv_area_pos),
        inv_area_size_x   (_inv_area_size_x),
        inv_area_size_y   (_inv_area_size_y)
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

    void draw(RenderTarget& render_target) override
    {
        canvas_renderer->display();

        Texture* texture = canvas_renderer->getTexture();
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

    // is point visible in canvas visible area
    bool isScreenPointInCanvas(const Point screen_pos)
    {
        if (screen_pos.x >= inv_area_pos.x                   &&
            screen_pos.x <= inv_area_pos.x + inv_area_size_x &&
            screen_pos.y >= inv_area_pos.y                   &&
            screen_pos.y <= inv_area_pos.y + inv_area_size_y)
        {
            return false;
        }

        return screen_pos.x >= original_host_pos.x                &&
               screen_pos.x <= original_host_pos.x + host_size_x  &&
               screen_pos.y >= original_host_pos.y                &&
               screen_pos.y <= original_host_pos.y + host_size_y;
    }

    bool isCellVisible(const Point pos_in_canvas, const size_t field_size)
    {
        return isCanvasPointVisible(pos_in_canvas)                                                     ||
               isCanvasPointVisible(Point(pos_in_canvas.x + field_size, pos_in_canvas.y))              ||
               isCanvasPointVisible(Point(pos_in_canvas.x             , pos_in_canvas.y + field_size)) ||
               isCanvasPointVisible(Point(pos_in_canvas.x + field_size, pos_in_canvas.y + field_size));
    }

    bool isCanvasPointVisible(const Point pos_in_canvas)
    {
        return pos_in_canvas.x >= relative_host_pos.x                &&
               pos_in_canvas.x <= relative_host_pos.x + host_size_x  &&
               pos_in_canvas.y >= relative_host_pos.y                &&
               pos_in_canvas.y <= relative_host_pos.y + host_size_y;
    }

private:
    Point original_host_pos;
    Point relative_host_pos;

    size_t host_size_x;
    size_t host_size_y;

    size_t canvas_size_x;
    size_t canvas_size_y;

    RenderTarget* canvas_renderer;

    Point  inv_area_pos;
    size_t inv_area_size_x;
    size_t inv_area_size_y;
};