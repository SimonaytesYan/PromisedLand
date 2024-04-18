#pragma once

#include "../../Interlayers/ViewInterlayer.hpp"
#include "../Widget/Widget.hpp"

class CellViewGroup;

const size_t kFieldSize = 64;

class CellView : public Widget
{
    friend CellViewGroup;

public:
    CellView(const Texture texture, const Point pos, 
             CellViewGroup& parent) 
    : Widget  (pos),
      texture (texture),
      parent  (parent)
    { }

    CellView(const Texture texture, const Point pos, 
             CellViewGroup& parent, size_t index_in_cell_group) 
    : Widget              (pos),
      texture             (texture),
      parent              (parent),
      index_in_cell_group (index_in_cell_group)
    {}

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
    }

    void push(const EventPtr event) override;
    void onClick(const Point point, const EventPtr event);

private:

    void setIndexInCellGroup(size_t index)
    { index_in_cell_group = index; }

    const Texture  texture;
    CellViewGroup& parent;
    size_t         index_in_cell_group;
};

