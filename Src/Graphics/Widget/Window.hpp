#pragma once

#include <vector>

#include "Widget.hpp"

class Window : public Widget
{
public:
    explicit Window(const Point position, CellInterlayer* _cell_interlayer = nullptr)
      : Widget          (position),
        children        (),
        cell_interlayer (_cell_interlayer)
    {}

    // Non-copyable
    Window          (const Window& other) = delete;
    Window operator=(const Window& other) = delete;

    // Non-movable
    Window          (Window&& other) = delete;
    Window operator=(Window&& other) = delete;

    void push(const Event* event) override
    {
        switch (event->event_type)
        {
        case EventType::TICK:
            cell_interlayer->pushToLogic(event);
            break;
        case EventType::BUILD_CELL_EVENT:
          {  
            const BuildCellEvent* build_event = static_cast<const BuildCellEvent*>(event);
            addChild(build_event->cell_view);
            break;
          }  
        default:
            break;
        }

        for (auto val : children)
            val->push(event);
    }

    void draw(RenderTarget& rt) override
    {
        for (auto child : children)
        {
            child->draw(rt);
        }
    } 

    void addChild(Widget* child)
    {
        children.push_back(child);
    }

    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    {
        cell_interlayer = _cell_interlayer;
    }

    void createCell(const Point position, const FieldType cell_type)
    {
        MouseEvent event(position);
        cell_interlayer->pushToLogic(&event);
    }

    ~Window()
    {
        // STLVectorDecor<Renderable*> children_traits(children);
        for (auto val : children)
        {
            delete val;
        }
    }

private:
    std::vector<Widget*> children;
    CellInterlayer*      cell_interlayer;
};