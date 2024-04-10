#pragma once

#include "../../Interlayers/ViewInterlayer.hpp"
#include "../Widget/Widget.hpp"

class CellInterlayer;

const size_t kFieldSize = 64;

class CellView : public Widget
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

    void push(const Event* event) override;
    void onClick(const Point point, const Event* event);

private:
    const Texture texture;
    CellInterlayer& interlayer;
};

