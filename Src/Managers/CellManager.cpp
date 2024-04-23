#include "CellManager.hpp"
#include "../Interlayers/CellInterlayer.hpp"
#include "../CellLoader/CellKeeper.hpp"

void CellManager::createCell(const Point position)
{
    Cell* new_cell = CellKeeper::createCell(cell_type);

    if (cell_type == static_cast<size_t>(ReservedTypes::HOUSE))
        cell_interlayer->pushToLogic(new NewCitizensEvent(static_cast<Building*>(new_cell)->getAppearIncome().population));

    createCell(new_cell);
    res_manager->onBuild(new_cell);
}

void CellManager::tryBuildCell(const size_t index, const Point position)
{
    if (CellKeeper::getType(cell_type) != CellType::BUILDING)
        return;

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
