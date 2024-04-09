#pragma once

#include "../../Eventable.hpp"
#include "../../Renderable.hpp"

class CellView : Eventable, Renderable 
{
public:
    void push(const Event* event) override
    {}

    void draw(RenderTarget& rt) override
    {} 
};