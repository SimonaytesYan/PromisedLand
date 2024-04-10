#pragma once

#include "../Renderable.hpp"
#include "../Events/Eventable.hpp"
#include "../../Utils/GraphicPrimitives.hpp"

class Widget : public Renderable, public Eventable
{ 
public:
    Widget(const int x = 0, const int y = 0) :
    point(x, y)
    { }

    Widget(const Point point) : 
    point (point)
    { }

protected:
    Point point;
};
