#pragma once

#include <vector>

#include "../../../Standart/Graphics/CellView/CellViewGroupI.hpp"

class CellInterlayer;
class CellView;

class CellViewGroup : public CellViewGroupI
{
    friend CellInterlayer;

public:
    CellViewGroup(const Point position)
    : CellViewGroupI (position)
    { }

    void push(const EventPtr event) override;
    virtual void pushToLogic(const EventPtr event);
    void draw(RenderTarget& rt) override;
    
    void setCellInterlayer(CellInterlayerI* _cell_interlayer) override
    { cell_interlayer = reinterpret_cast<CellInterlayer*>(_cell_interlayer); }

    ~CellViewGroup()
    {
        for (auto val : cell_views)
            delete val;
    }

protected:
    // Put here pointers, created by new.
    // Here you transfer ownership of cell to CellViewGroup
    void addCell(CellView* cell_view) override;
    void addCell(const FieldType field_type, const Point pos) override;

    void deleteDeadCells() override;

    std::vector<CellView*> cell_views;   // CellViewGroup own it
    CellInterlayer*        cell_interlayer;
};