#pragma once

#include <vector>

#include "Canvas.hpp"
#include "../../Constants.hpp"
#include "../../Map/MapSaveLoad.hpp"

class CellInterlayer;
class CellView;

class CellViewGroup : public Widget
{
    friend CellInterlayer;
    friend MapSaverLoader;

public:
    CellViewGroup(const Point position, const size_t _map_size_x, const size_t _map_size_y);

    void push(const EventPtr event) override;
    virtual void pushToLogic(const EventPtr event);
    void draw(RenderTarget& rt) override;
    
    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    { cell_interlayer = _cell_interlayer; }

    ~CellViewGroup()
    {
        delete draw_canvas;
        
        for (auto val : cell_views)
            delete val;
    }

protected:
    // Put here pointers, created by new.
    // Here you transfer ownership of cell to CellViewGroup
    void addCell(CellView* cell_view);
    void addCell(const FieldType field_type, const Point pos);

    void deleteDeadCells();

    std::vector<CellView*> cell_views;   // CellViewGroup own it
    CellInterlayer*        cell_interlayer;
    Canvas*                draw_canvas;
};