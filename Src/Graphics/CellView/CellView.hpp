#pragma once

#include  "../Widget/Widget.hpp"

class CellView : Widget
{
public:
    CellView(const Texture texture, const int x = 0, const int y = 0) 
    : Widget  (x, y),
      texture (texture)
    { }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
    }

    void push(const Event* event) override
    { }

private:
    const Texture texture;
};

