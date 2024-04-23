#include "CellManager.hpp"
#include "../Interlayers/CellInterlayer.hpp"
#include "../CellLoader/CellKeeper.hpp"

void CellManager::createCell(const Point position)
{
    Cell* new_cell = CellKeeper::createCell(cell_type);

    // TODO:
    // if (cell_type == FieldType::House)
    //     cell_interlayer->pushToLogic(new NewCitizensEvent(static_cast<House*>(new_cell)->getAppearIncome().population));

    createCell(new_cell);
    res_manager->onBuild(new_cell);
}

void CellManager::tryBuildCell(const size_t index, const Point position)
{
    // TODO:
    // if (cell_type <= FieldType::CellNumber || FieldType::FieldNumber <= cell_type)
    //     return;

    const unsigned char on_which_build = static_cast<unsigned char>(cells[index]->getFieldType());
    const Bitmask       build_mask     = CellKeeper::getBuildMask(cell_type);    
    
    bool able_to_build = res_manager->tryBuild(cell_type);
    if (!able_to_build) return;
    
    if (getBit(build_mask, on_which_build))
    {
        deleteCell(index);
        createCell(position);

        cell_interlayer->pushToView(new RebuildEvent(index, cell_type));
    }
}
