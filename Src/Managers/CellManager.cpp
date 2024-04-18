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
    
    const unsigned char on_which_build = static_cast<unsigned char>(cells[index]->getFieldType());
    const Bitmask       build_mask     = static_cast<Building*>    (new_building)->getBuildMask();

    fprintf(stderr, "build_mask        = %b\n", build_mask);
    fprintf(stderr, "new_building type = %d\n", new_building->getFieldType());
    fprintf(stderr, "on_which_build    = %d\n", on_which_build);
    delete new_building;
    
    if (getBit(build_mask, on_which_build))
    {
        fprintf(stderr, "Rebuild\n");
        deleteCell(index);
        createCell(position);

        cell_interlayer->pushToView(new RebuildEvent(index, cell_type));
    }
}
