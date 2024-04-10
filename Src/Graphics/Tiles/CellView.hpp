#pragma once

#include "../../Interlayers/CellInterlayer.hpp"
#include "../Widget/Widget.hpp"

class CellView : public Widget 
{
public:
    explicit CellView(const Point position, const FieldType field_type, CellInterlayer& interlayer)
      : Widget     (position),
        interlayer (interlayer)
    {
        // spend some resources on build
        // we should discuss it
        Event create_event(EventType::MOUSE_CLICK);
        view_manager.pushToLogic(&create_event);
    }

    void push(const Event* event) override
    {
        switch (event->event_type)
        {
            case EventType::MOUSE_CLICK:
                if ()
                interlayer.pushToLogic(event);
                break;
            
            default:
                break;
        }
    }

    virtual void draw(RenderTarget& rt) override
    {} 

private:
    CellInterlayer& interlayer;
};