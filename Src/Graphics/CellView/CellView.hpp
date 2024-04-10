#pragma once

#include "../../Interlayers/ViewInterlayer.hpp"
#include "../Widget/Widget.hpp"
// #include "../../Interlayers/CellInterlayer.hpp"

const size_t kFieldSize = 64;

class CellView : public Widget
{
public:
    CellView(const Texture texture, Point pos, const FieldType field_type, ViewInterlayer& interlayer) 
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
            interlayer.pushToLogic(event);
            break;
        
        default:
            break;
        }
    }

private:
    const Texture texture;
    ViewInterlayer& interlayer;
};

