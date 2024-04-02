#pragma once
#include "RenderTarget.h"

class Drawable
{
public:
    virtual void draw(RenderTarget& render_target) = 0; 
};
