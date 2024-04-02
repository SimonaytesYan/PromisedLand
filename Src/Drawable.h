#pragma once
#include "RenderTarget.h"

class Drawable
{
    virtual void draw(const RenderTarget& render_taget) = 0; 
};
