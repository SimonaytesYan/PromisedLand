#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType ForestInterface::getType() 
{
    return CellType::CELL;
}

Cell* ForestInterface::createCell() 
{
    return new ForestCell();
}

CellView* ForestInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new ForestView(pos, cell_view_group);
}

Bitmask ForestInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources ForestInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t ForestInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::FOREST);
}

CellInterface* getCellInterface()
{
    return new ForestInterface();
}