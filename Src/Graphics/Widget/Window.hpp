#pragma once

#include <vector>

#include "Widget.hpp"

class Window : public Widget
{
public:
    explicit Window(const Point position, CellInterlayer* _cell_interlayer = nullptr)
      : Widget          (position),
        children        ()
    {}

    // Non-copyable
    Window          (const Window& other) = delete;
    Window operator=(const Window& other) = delete;

    // Non-movable
    Window          (Window&& other) = delete;
    Window operator=(Window&& other) = delete;

    void push(const EventPtr event) override
    {
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

    ~Window()
    {
        for (auto val : children)
        {
            delete val;
        }
    }

private:
    std::vector<Widget*> children;
};