#pragma once

#include <functional>

#include "Widget.hpp"
#include "../../Utils/Functor.hpp"

class Button : public Widget
{
public:
    Button(Point pos, size_t x_len, size_t y_len, BasicFunctor* func,
           const char* imp_path) :
    Widget   (pos),
    x_len    (x_len),
    y_len    (y_len),
    on_click (std::move(func)),
    texture  (imp_path)
    { }
    
    void draw(RenderTarget& render_target)
    {
        render_target.drawTexture(pos, texture);
    }

    void push(const Event* event) override
    {
        switch (event->event_type)
        {
            case EventType::MOUSE_CLICK:
                onClick(static_cast<const MouseEvent*>(event)->pos);
                break;
            
            default:
                break;
        }
    }

    bool onClick(const Point point)
    {
        if (pos.x <= point.x && point.x <= pos.x + x_len &&
            pos.y <= point.y && point.y <= pos.y + y_len)
        {
            (*on_click)();
            return true;
        }
        return false;
    }

    void onTick()
    { }

    ~Button()
    {
        delete on_click;
    }

private:
    size_t        x_len;
    size_t        y_len;
    Texture       texture;
    BasicFunctor* on_click;
};
