#pragma once

#include "../Utils/RenderTarget.hpp"

struct Renderable 
{
    virtual void draw(RenderTarget& rt) = 0;
    virtual ~Renderable() = default;
};