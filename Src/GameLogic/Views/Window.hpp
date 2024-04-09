#pragma once

#include <vector>

#include "../Eventable.hpp"
#include "../Renderable.hpp"
// #include "../../../StlVector/Src/VectorDecor.hpp"
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
    {
        for (auto child : children)
        {
            child->draw(rt);
        }
    } 

    void addChild(Renderable* child)
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
    Point                    position;
    WindowViewManager        view_manager;
    std::vector<Renderable*> children;
};