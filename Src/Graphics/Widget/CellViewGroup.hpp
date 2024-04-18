#pragma once

#include "Widget.hpp"
#include "../CellView/CellView.hpp"
#include "../../Interlayers/CellInterlayer.hpp"

class CellViewGroup : public Widget
{
public:
    CellViewGroup(const Point position)
    : Widget(position)
    { }

    void push(const EventPtr event) override;

    void pushToLogic(const EventPtr event)
    { cell_interlayer->pushToLogic(event); }

    void draw(RenderTarget& rt) override;

    void addCell(const Texture texture, const Point pos)
    {
        const size_t index = cell_views.size();
        cell_views.push_back(new CellView(texture, pos, *this, index));
    }

    // Put here pointers, created by new.
    // Here you transfer ownership of cell to CellViewGroup
    void addCell(CellView* cell_view)
    { 
        cell_views.push_back(cell_view);
        cell_view->setIndexInCellGroup(cell_views.size() - 1);
    }
    
    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    { cell_interlayer = _cell_interlayer; }

    ~CellViewGroup()
    {
        for (auto val : cell_views)
            delete val;
    }

protected:
    void deleteDeadCells();
    void addCell(const FieldType field_type, const Point pos);

    std::vector<CellView*> cell_views;   // CellViewGroup own it
    CellInterlayer*        cell_interlayer;
};
