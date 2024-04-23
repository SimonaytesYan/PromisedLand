#pragma once

#include <vector>

#include "ViewInterlayer.hpp"
#include "LogicInterlayer.hpp"
#include "../Managers/CellManager.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"

class CellInterlayer : public ViewInterlayer, public LogicInterlayer
{
public:
    explicit CellInterlayer(CellManager& cell_manager)
      : cell_manager    (cell_manager),
        cell_view_group (nullptr)
    { }

    void pushToView(const EventPtr event) override;
    void pushToLogic(const EventPtr event) override;

    void setCellViewGroup(CellViewGroup* new_cell_view_group)
    { cell_view_group = new_cell_view_group; }

    void createCell(const size_t filed_type, const Point pos);

private:
    CellManager&   cell_manager;
    CellViewGroup* cell_view_group;
};