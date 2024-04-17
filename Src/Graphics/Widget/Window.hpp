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

    void push(const EventPtr event) override
    {
        
        switch (event->event_type)
        {
        case EventType::TICK:
            cell_interlayer->pushToLogic(event);
            break;
        case EventType::BUILD_CELL_EVENT:
          {  
            const BuildCellEvent* build_event = static_cast<const BuildCellEvent*>(event.get());
            addChild(build_event->cell_view);
            break;
          }  
        case EventType::DESTROY_CELL_EVENT:
          {  
            const DestroyCellEvent* delete_event = static_cast<const DestroyCellEvent*>(event.get());
            delete_event->cell_view->kill();

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
        auto begin_iterator = children.begin() - 1;
        auto end_iterator   = children.end()   - 1;

        for (; end_iterator != begin_iterator; --end_iterator)
        {
            if (!((*end_iterator)->isAlive()))
            {
                delete (*end_iterator);
                children.erase(end_iterator);
            }
            
            (*end_iterator)->draw(rt);
            
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
        cell_interlayer->pushToLogic(new MouseEvent(position));
    }

    ~Window()
    {
        for (auto val : children)
        {
            delete val;
        }
    }

private:
    std::vector<Widget*> children;
    CellInterlayer*      cell_interlayer;
};