#pragma once

#include "../Renderable.hpp"
#include "../../Events/Eventable.hpp"
#include "../../Utils/GraphicPrimitives.hpp"

class Widget : public Renderable, public Eventable
{ 
public:
    Widget(const int x = 0, const int y = 0) :
    pos      (x, y),
    is_alive (true)
    { }

    Widget(const Point pos) : 
    pos      (pos),
    is_alive (true)
    { }

    virtual void kill()
    {
        is_alive = false;
    }

    virtual bool isAlive()
    {
        return is_alive;
    }

protected:
    Point pos;
    bool  is_alive;
};
