#pragma once

#include  "../Widget/Widget.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

const size_t kFieldSize = 64;

class CellView : Widget
{
public:
    CellView(const Texture texture, Point pos, const FieldType field_type, CellInterlayer& interlayer) 
    : Widget     (pos),
      texture    (texture),
      interlayer (interlayer)
    { }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
    }

    void push(const Event* event) override
    { }

private:
    const Texture texture;
    CellInterlayer& interlayer;
};

