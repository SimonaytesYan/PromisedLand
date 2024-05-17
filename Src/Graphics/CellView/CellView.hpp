#pragma once

#include "../../GameLogic/Tiles/Cell.hpp"
#include "../Widget/Widget.hpp"
#include "../Widget/CellViewGroup.hpp"

const size_t kFieldSize = 64;

class CellView : public Widget
{
public:
    CellView(const TextureI texture, const Point pos, 
             CellViewGroup& parent) 
    : Widget        (pos),
      texture       (texture),
      parent        (parent),
      is_chosen     (false),
      display_coeff (false),
      cur_workers   (0),
      max_workers   (0)
    { }

    CellView(const TextureI texture, const Point pos, 
             CellViewGroup& parent, size_t index_in_cell_group) 
    : Widget              (pos),
      texture             (texture),
      parent              (parent),
      index_in_cell_group (index_in_cell_group),
      is_chosen           (false),
      display_coeff       (false),
      cur_workers         (0),
      max_workers         (0)
    {}

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
        if (display_coeff)
        {
            render_target.drawCircle(pos, kCoeffTextSize, kCircleColor);

            std::string str = std::to_string(cur_workers) + "/" + std::to_string(max_workers);
            render_target.drawText({pos.x + kCoeffTextSize / 4, pos.y + kCoeffTextSize / 4}, str.c_str(), kCoeffTextSize, kCoeffTextColor);
        }
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

    void setCoeff(long int _cur_workers, long int _max_workers)
    {
        display_coeff = true;
        cur_workers   = _cur_workers;
        max_workers   = _max_workers;
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
    
private:
    const Color    kChosenCellColor = {255, 255, 255, 128};
    const Color    kCoeffTextColor  = {0, 0, 0};
    const Color    kCircleColor     = {255, 0, 0};
    const uint16_t kCoeffTextSize   = 10;

    const TextureI  texture;
    CellViewGroup&  parent;
    size_t          index_in_cell_group;
    bool            is_chosen;  

    bool            display_coeff;
    long int        cur_workers;
    long int        max_workers;
};