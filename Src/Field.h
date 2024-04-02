#pragma once

#include "EventProcessable.h"

class Field : EventProcessable
{
    virtual void draw();
//==================EVENTS============= 
    virtual bool onClick(int x, int y);
};


