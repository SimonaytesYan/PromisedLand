#pragma once

#include "../../Managers/CellViewManager.hpp"
#include "../../Eventable.hpp"
#include "../../Renderable.hpp"

class CellView : public Eventable, public Renderable 
{
public:
    void push(const Event* event) override
    {}

    void draw(RenderTarget& rt) override
    {} 
};