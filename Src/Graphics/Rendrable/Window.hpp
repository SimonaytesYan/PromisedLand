#pragma once

#include <vector>

#include "Widget.hpp"

class Window : public Widget
{
public:
    explicit Window(const Point position)
      : Widget   (position),
        children ()
    {}

    // Non-copyable
    Window          (const Window& other) = delete;
    Window operator=(const Window& other) = delete;

    // Non-movable
    Window          (Window&& other) = delete;
    Window operator=(Window&& other) = delete;

    void push(const Event* event) override
    {
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
};