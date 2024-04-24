#pragma once

#include "../../GameLogic/Cell.hpp"
#include "../Widget.hpp"
#include "CellViewGroupI.hpp"

const size_t kFieldSize = 64;

class CellView : public Widget
{
public:
    CellView(const Texture texture, const Point pos, 
             CellViewGroupI& parent) 
    : Widget    (pos),
      texture   (texture),
      parent    (parent),
      is_chosen (false)
    { }

    CellView(const Texture texture, const Point pos, 
             CellViewGroupI& parent, size_t index_in_cell_group) 
    : Widget              (pos),
      texture             (texture),
      parent              (parent),
      index_in_cell_group (index_in_cell_group),
      is_chosen           (false)
    {}

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
        if (is_chosen) 
        {
            render_target.drawRect(pos, {kFieldSize, kFieldSize}, kChosenCellColor);
        }
    }

    void push(const EventPtr event) override
    {
        switch (event->event_type)
        {
        case EventType::MOUSE_CLICK:
          {
            const MouseClickEvent* mouse_event = static_cast<const MouseClickEvent*>(event.get());
            onClick(mouse_event->pos, event);
            break;
          }
        case EventType::MOUSE_MOVE:
          {
            const MouseMoveEvent* mouse_event = static_cast<const MouseMoveEvent*>(event.get());
            onMouseMove(mouse_event->pos);
            break;
          }
        default:
            break;
        }
    }
    void onClick(const Point point, const EventPtr event)
    {
        if (pos.x < point.x && point.x < pos.x + kFieldSize &&
        pos.y < point.y && point.y < pos.y + kFieldSize)
        {
            parent.pushToLogic(new TryBuildEvent(index_in_cell_group, pos));
        }
    }
    void onMouseMove(const Point point)
    {
        if (pos.x < point.x && point.x < pos.x + kFieldSize &&
            pos.y < point.y && point.y < pos.y + kFieldSize)
        {
            is_chosen = true;
        }
        else
        {
            is_chosen = false;
        }
    }

    void setIndexInCellGroup(size_t index)
    { index_in_cell_group = index; }

    size_t getIndex() const 
    {
        return index_in_cell_group;
    }

    Point getPos() const 
    {
        return pos;
    }
    

protected:
    const Color kChosenCellColor = {255, 255, 255, 128};

    const Texture   texture;
    CellViewGroupI& parent;
    size_t          index_in_cell_group;
    bool            is_chosen;  
};