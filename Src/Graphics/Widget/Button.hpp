#pragma once

#include <functional>

#include "Widget.hpp"

typedef void (*Function)(void* args);

class Functor
{
public:
    Functor(Function function, void* args) :
    func(function),
    args(args)
    { }

    void operator()()
    {
        func(args);
    }

    ~Functor()
    { 
        // delete args;
    }

protected:
    Function func;
    void*    args;
};

class Button : public Widget
{
public:
    Button(Point pos, size_t x_len, size_t y_len, const Functor& func, 
           const char* imp_path) :
    Widget   (pos),
    x_len    (x_len),
    y_len    (y_len),
    on_click (func),
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
        // printf("Button::onClick(%lf %lf)\n", pos.x, pos.y);
        // printf("Button::onClick(%lf %lf)\n", point.x, point.y);
        if (pos.x <= point.x && point.x <= pos.x + x_len &&
            pos.y <= point.y && point.y <= pos.y + y_len)
        {
            on_click();
            return true;
        }
        return false;
    }

    void onTick()
    { }

private:
    size_t  x_len;
    size_t  y_len;
    Texture texture;
    Functor on_click;
};
