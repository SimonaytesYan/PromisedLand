#pragma once

#include "../../Managers/CellViewManager.hpp"
#include "../../Eventable.hpp"
#include "../../Renderable.hpp"

class CellView : public Eventable, public Renderable 
{
public:
    explicit CellView(const Point _position, const FieldType _field_type, ResourceManager& _res_manager)
      : position     (_position),
        view_manager (_field_type, _res_manager)
    {
        // spend some resources on build
        // we should discuss it
        Event create_event(EventType::MOUSE_CLICK);
        view_manager.pushToLogic(&create_event);
    }

    void push(const Event* event) override
    {}

    void draw(RenderTarget& rt) override
    {} 

private:
    Point           position;
    CellViewManager view_manager;
};