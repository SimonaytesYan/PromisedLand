#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType IslandInterface::getType() 
{
    return CellType::CELL;
}

Cell* IslandInterface::createCell() 
{
    return new IslandCell();
}

CellView* IslandInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new IslandView(pos, cell_view_group);
}

Bitmask IslandInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources IslandInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t IslandInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::ISLAND);
}

const char* IslandInterface::getAsset()
{
    return kViewAsset;
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new IslandInterface();
}