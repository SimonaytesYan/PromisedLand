#pragma once

#include <vector>

#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Map/MapSaveLoad.hpp"

class CellManager;

class CellInterlayer
{
    friend MapSaverLoader;

public:
    explicit CellInterlayer(CellManager& cell_manager)
      : cell_manager    (cell_manager),
        cell_view_group (nullptr)
    { }

    void pushToView(const EventPtr event);
    void pushToLogic(const EventPtr event);

    void setCellViewGroup(CellViewGroup* new_cell_view_group)
    { cell_view_group = new_cell_view_group; }

    void createCell(const size_t filed_type, const Point pos);

private:
    CellManager&   cell_manager;
    CellViewGroup* cell_view_group;
};