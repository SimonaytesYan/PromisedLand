#pragma once

#include "LogicInterlayer.hpp"
#include "ViewInterlayer.hpp"

#include "../Utils/GraphicPrimitives.hpp"

class CellViewGroup;

struct CellInterlayerI : public ViewInterlayer, public LogicInterlayer
{
    virtual void setCellViewGroup(CellViewGroup* new_cell_view_group) = 0;
    virtual void createCell(const size_t filed_type, const Point pos) = 0;
};