#pragma once

#include "../Utils/RenderTargetI.hpp"

class Renderable
{
public:
    virtual void draw(RenderTargetI& render_target) = 0;

    virtual ~Renderable() = default;
};