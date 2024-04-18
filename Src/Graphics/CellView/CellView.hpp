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
      interlayer (interlayer),
      is_chosen  (false)
    { }

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
        if (is_chosen) 
        {
            render_target.drawRect(pos, {kFieldSize, kFieldSize}, kChosenCellColor);
        }
    }

    void push(const EventPtr event) override;
    void onClick(const Point point, const EventPtr event);
    void onMouseMove(const Point point);

private:

    static Color kChosenCellColor;

private:
    const Texture   texture;
    CellInterlayer& interlayer;
    bool            is_chosen;
};

