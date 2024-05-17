#pragma once

#include <cstring>

#include "../../Graphics/Widget/DumyWidget.hpp"
#include "../../Utils/RenderTarget.hpp"
#include "Widget.hpp"

class Toast : public Widget
{
public:

    explicit Toast(const Point pos, const char* message, EventManager& event_manager, DummyWidget& parent, const unsigned duration = 2)
      : Widget          (pos),
        message         (message),
        duration        (duration),
        parent          (parent),
        event_manager   (event_manager),
        active_tick_cnt (0)
    {
        parent       .addChild(this);
        event_manager.addChild(this);
    }

    void push(const EventPtr event) override 
    {
        if (event->event_type == EventType::TICK) 
        {
            active_tick_cnt++;
        }
    }

    void draw(RenderTarget& render_target)
    {   
        render_target.drawRect(pos, {std::strlen(message) * kCharSize, kCharSize}, kBackColor);
        render_target.drawText(pos, message, kCharSize, kTextColor);
        if (active_tick_cnt >= duration)
        {
            parent       .removeChild(this);
            event_manager.removeChild(this);
        }
    }

private:
    const uint16_t kCharSize  = 10;
    const Color    kTextColor = Color::Green;
    const Color    kBackColor = Color::Magenta;

    const char*    message;
    const unsigned duration;    // tick cnt
    DummyWidget&   parent;
    EventManager&  event_manager;

    unsigned active_tick_cnt;
};