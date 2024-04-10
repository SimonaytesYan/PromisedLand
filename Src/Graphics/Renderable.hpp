#pragma once

#include "../Utils/RenderTarget.hpp"

class Renderable
{
public:
    virtual void draw(RenderTarget& render_target);
};
