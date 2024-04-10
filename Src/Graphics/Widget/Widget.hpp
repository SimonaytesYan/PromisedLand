#pragma once

#include "../Renderable.hpp"
#include "../Events/Eventable.hpp"
#include "../../Utils/GraphicPrimitives.hpp"

class Widget : public Renderable, public Eventable
{ 
public:
    Widget(const int x = 0, const int y = 0) :
    pos(x, y)
    { }

    Widget(const Point pos) : 
    pos (pos)
    { }

protected:
    Point pos;
};
