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
    
    const unsigned char on_which_build    = static_cast<unsigned char>(cells[index]->getFieldType());
          Building*     building_instance = static_cast<Building*>(new_building);
    const Bitmask       build_mask        = building_instance->getBuildMask();
    
    bool able_to_build = res_manager->tryBuild(building_instance);

    delete new_building;

    if (!able_to_build) return;
    
    if (getBit(build_mask, on_which_build))
    {
        deleteCell(index);
        createCell(position);

        cell_interlayer->pushToView(new RebuildEvent(index, cell_type));
    }
}
