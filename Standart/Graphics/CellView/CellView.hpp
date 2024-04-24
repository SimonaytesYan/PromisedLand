#pragma once

#include "../../GameLogic/Cell.hpp"
#include "../Widget.hpp"

class CellViewGroup;

const size_t kFieldSize = 64;

class CellView : public Widget
{
    friend CellViewGroup;

public:
    CellView(const Texture texture, const Point pos, 
             CellViewGroup& parent) 
    : Widget    (pos),
      texture   (texture),
      parent    (parent),
      is_chosen (false)
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
        if (is_chosen) 
        {
            render_target.drawRect(pos, {kFieldSize, kFieldSize}, kChosenCellColor);
        }
    }

    void push(const EventPtr event) override;
    virtual void onClick(const Point point, const EventPtr event);
    virtual void onMouseMove(const Point point);

private:
    void setIndexInCellGroup(size_t index)
    { index_in_cell_group = index; }

private:
    static Color   kChosenCellColor;
    const Texture  texture;
    CellViewGroup& parent;
    size_t         index_in_cell_group;
    bool           is_chosen;    
};

