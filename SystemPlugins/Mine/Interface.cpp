#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType MineInterface::getType() 
{
    return CellType::BUILDING;
}

Cell* MineInterface::createCell() 
{
    return new MineCell();
}

CellView* MineInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new MineView(pos, cell_view_group);
}

Bitmask MineInterface::getBuildMask() 
{
    return kBuildMask;
}

Resources MineInterface::getAppearIncome() 
{
    return kAppearIncome;
}

size_t MineInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::MINE);
}

const char* MineInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new MineInterface();
}