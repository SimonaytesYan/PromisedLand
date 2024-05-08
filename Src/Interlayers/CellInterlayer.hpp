#pragma once

#include <vector>

#include "../../Standart/Interlayers/CellInterlayerI.hpp"
#include "../Managers/CellManager.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Map/MapSaveLoad.hpp"

class CellInterlayer : public CellInterlayerI
{
    friend MapSaver;

public:
    explicit CellInterlayer(CellManager& cell_manager)
      : cell_manager    (cell_manager),
        cell_view_group (nullptr)
    { }

    void pushToView(const EventPtr event) override;
    void pushToLogic(const EventPtr event) override;

    void setCellViewGroup(CellViewGroup* new_cell_view_group) override
    { cell_view_group = new_cell_view_group; }

    void createCell(const size_t filed_type, const Point pos) override;

private:
    CellManager&   cell_manager;
    CellViewGroup* cell_view_group;
};