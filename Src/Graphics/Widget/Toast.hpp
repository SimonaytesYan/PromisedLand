#pragma once

#include <cstring>

#include "../../Graphics/Widget/DumyWidget.hpp"
#include "../../Utils/RenderTarget.hpp"
#include "Widget.hpp"

static const uint16_t kCharSize    = 20;
static const size_t   kToastWidth  = 200;
static const size_t   kToastHeight = 40;

class Toast : public Widget
{
public:

    explicit Toast(const size_t win_size_x, const size_t win_size_y, const char* message, EventManager& event_manager, DummyWidget& parent, const unsigned duration = 2)
      : Widget          (win_size_x - kToastWidth - kBorderIndent, kBorderIndent),
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
        render_target.drawRect(pos, {kToastWidth, kToastHeight}, kBackColor);
        render_target.drawText(pos, message, kCharSize, kTextColor);

        if (active_tick_cnt >= duration)
        {
            active_tick_cnt = 0;

            parent       .removeChild(this);
            event_manager.removeChild(this);

            delete this;
        }
    }

private:
    const Color kTextColor  = Color::Black;
    const Color kBackColor  = Color::Magenta;

    const char*    message;
    const unsigned duration;    // tick cnt
    DummyWidget&   parent;
    EventManager&  event_manager;

    unsigned active_tick_cnt;
};