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

void CellManager::tryBuildCell(const size_t index, const Point position)
{
    Cell* new_building = Cell::createInstance(cell_type);
    if (getBit(static_cast<Building*>    (new_building)->getBuildMask(), 
               static_cast<unsigned char>(cells[index]->getFieldType())))
    {
        deleteCell(index);
        createCell(position);

        cell_interlayer->pushToView(new RebuildEvent(index, cell_type));
    }
    else
        delete new_building;
}
