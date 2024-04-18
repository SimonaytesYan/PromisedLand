#include "CellManager.hpp"
#include "../Interlayers/CellInterlayer.hpp"

void CellManager::createCell(const Point position)
{
    Cell* new_cell = Cell::createInstance(cell_type);

    if (cell_type == FieldType::House)
        cell_interlayer->pushToLogic(new NewCitizensEvent(static_cast<House*>(new_cell)->getAppearIncome().population));

    createCell(new_cell);
    res_manager->onBuild(new_cell);
}