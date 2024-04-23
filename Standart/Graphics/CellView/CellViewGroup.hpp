#pragma once

#include <vector>

#include "CellView.hpp"
#include "../Widget.hpp"

class CellInterlayer;

class CellViewGroup : public Widget
{
    friend CellInterlayer;

public:
    CellViewGroup(const Point position)
    : Widget(position)
    { }

    void push(const EventPtr event) override;
    virtual void pushToLogic(const EventPtr event);
    void draw(RenderTarget& rt) override;
    
    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    { cell_interlayer = _cell_interlayer; }

    ~CellViewGroup()
    {
        for (auto val : cell_views)
            delete val;
    }

protected:
    // Put here pointers, created by new.
    // Here you transfer ownership of cell to CellViewGroup
    virtual void addCell(CellView* cell_view);
    virtual void addCell(const FieldType field_type, const Point pos);

    virtual void deleteDeadCells();

    std::vector<CellView*> cell_views;   // CellViewGroup own it
    CellInterlayer*        cell_interlayer;
};