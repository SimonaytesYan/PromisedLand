#pragma once

#include "EventProcessable.h"
#include "Drawable.h"

class GameObject : public EventProcessable, public Drawable
{
public:
    GameObject() : 
    x (x),
    y (y)
    { }

    GameObject(int x, int y) :
    x (x),
    y (y)
    { }

protected:
    int x;
    int y;
};