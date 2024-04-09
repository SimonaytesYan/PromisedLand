#pragma once

#include "../Eventable.hpp"
#include "../Renderable.hpp"
#include "../../../StlVector/Src/VectorDecor.hpp"
#include "../Managers/WindowViewManager.hpp"

class Window : public Renderable, public Eventable
{
public:
    explicit Window(const Point _position, ResourceManager& _res_manager)
      : position     (_position),
        view_manager (_res_manager),
        children     ()
    {}

    // Non-copyable
    Window          (const Window& other) = delete;
    Window operator=(const Window& other) = delete;

    // Non-movable
    Window          (Window&& other) = delete;
    Window operator=(Window&& other) = delete;

    void push(const Event* event) override
    {
        view_manager.pushToLogic(event);
    }

    void draw(RenderTarget& rt) override
    {} 

    ~Window()
    {
        STLVectorDecor<Renderable*> children_traits(children);
        for (auto val : children_traits)
        {
            delete val;
        }
    }

private:
    Point               position;
    WindowViewManager   view_manager;
    Vector<Renderable*> children;
};