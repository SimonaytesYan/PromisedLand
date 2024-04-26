#pragma once

#include <vector>

#include "../Widget.hpp"
#include "../../Interlayers/CellInterlayerI.hpp"
#include "../../GameLogic/Cell.hpp"

class CellView;

class CellViewGroupI : public Widget
{
public:
    explicit CellViewGroupI(const Point position)
      :  Widget (position)
    {}

    virtual void pushToLogic      (const EventPtr event)              = 0;
    virtual void setCellInterlayer(CellInterlayerI* _cell_interlayer) = 0;
    
    virtual ~CellViewGroupI() = default;

protected:
    // Put here pointers, created by new.
    // Here you transfer ownership of cell to CellViewGroup
    virtual void addCell        (CellView* cell_view)                        = 0;
    virtual void addCell        (const FieldType field_type, const Point pos) = 0;
    virtual void deleteDeadCells()                                            = 0;
};