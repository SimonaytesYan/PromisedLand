#pragma once

#include <functional>

#include "../../Events/Events.hpp"
#include "Widget.hpp"
#include "../../Utils/Functor.hpp"
#include "../../Utils/RenderTarget.hpp"

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

    Button(const Button& other) :
    Widget   (other.pos),
    x_len    (other.x_len),
    y_len    (other.y_len),
    on_click (other.on_click->clone()),
    texture  (other.texture)
    { }

    Button(Button&& other) :
    Widget   (other.pos),
    x_len    (other.x_len),
    y_len    (other.y_len),
    on_click (std::move(other.on_click)),
    texture  (other.texture)
    { 
        other.on_click = nullptr;
    }

    Button operator=(const Button& other)
    {
        delete on_click;
        
        x_len    = other.x_len;
        y_len    = other.y_len;
        on_click = other.on_click->clone();
        texture  = other.texture;
    }


    void draw(RenderTargetI& render_target)
    {
        render_target.drawTexture(pos, texture);
    }

    void push(const EventPtr event) override
    {
        switch (event->event_type)
        {
            case EventType::MOUSE_CLICK:
                onClick(static_cast<const MouseClickEvent*>(event.get())->pos);
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
