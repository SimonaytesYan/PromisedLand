#pragma once

#include "../../Events/EventManager.hpp"
#include "../../Utils/RenderTarget.hpp"
#include "Widget.hpp"

class Toast : public Widget
{
    explicit Toast(const Point pos, const char* message, EventManager& event_man, const unsigned duration = 2)
      : Widget          (pos),
        message         (message),
        duration        (duration),
        event_man       (event_man),
        active_tick_cnt (0)
    {}

    void push(const EventPtr event) override {}
    void draw(RenderTarget& render_target)
    {
        render_target.drawText(pos, message, char_size, text_color);
        if (active_tick_cnt >= duration)
        {
            event_man.removeChild(this);
        }

        active_tick_cnt++;
    }

private:
    const uint16_t char_size  = 10;
    const Color    text_color = Color::Green;

    const char*    message;
    const unsigned duration;    // tick cnt
    EventManager&  event_man;

    unsigned active_tick_cnt;
};