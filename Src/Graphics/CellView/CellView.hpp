#pragma once

#include  "../Widget/Widget.hpp"

class CellView : Widget
{
public:
    CellView(const Texture texture, const int x = 0, const int y = 0) :
    texture (texture),
    x       (x),
    y       (y)
    { }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(Point(x, y), texture);
    }

private:
    const Texture texture;
    
    int x;
    int y;
};

