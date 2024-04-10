#pragma once

#include  "../Widget/Widget.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

const size_t kFieldSize = 64;

class CellView : Widget
{
public:
    CellView(const Texture texture, Point pos, const FieldType field_type, CellInterlayer& interlayer) 
    : Widget     (pos),
      texture    (texture),
      interlayer (interlayer)
    { }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
    }

    void push(const Event* event) override
    { 
        switch (event->event_type)
        {
        case EventType::MOUSE_CLICK:
            // TODO push CellEvent
            break;
        
        default:
            break;
        }
    }

private:
    const Texture texture;
    CellInterlayer& interlayer;
};

