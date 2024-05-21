#pragma once

#include <vector>

#include "Widget.hpp"
#include "../../Utils/RenderTarget.hpp"

class Window : public Widget
{
public:
    explicit Window(const Point position, size_t _map_size_x, size_t _map_size_y, const char* img_path)
      : Widget     (position),
        children   (),
        background (img_path),
        map_size_x (_map_size_x),
        map_size_y (_map_size_y)
    {}

    // Non-copyable
    Window          (const Window& other) = delete;
    Window operator=(const Window& other) = delete;

    // Movable
    Window (Window&& other) : 
    Widget     (other.pos),
    children   (std::move(other.children)),
    background (std::move(other.background))
    { }

    Window operator=(Window&& other) = delete;

    void push(const EventPtr event) override
    {
        for (auto val : children)
        {
            val->push(event);
        }
    }

    void draw(RenderTarget& rt) override
    {
        rt.drawTexture(this->pos, background);

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

    virtual ~Window()
    {
        for (auto val : children)
        {
            delete val;
        }
    }

private:
    std::vector<Widget*> children;
    Texture              background;

    size_t map_size_x;
    size_t map_size_y;
};
