#include "Cell.hpp"
#include "View.hpp"

#include "Interface.hpp"

CellType WaterInterface::getType() 
{
    return CellType::CELL;
}

Cell* WaterInterface::createCell() 
{
    return new WaterCell();
}

CellView* WaterInterface::createCellView(const Point pos, CellViewGroupI& cell_view_group)
{
    return new WaterView(pos, cell_view_group);
}

Bitmask WaterInterface::getBuildMask() 
{
    return 0;   // not a building
}

Resources WaterInterface::getAppearIncome() 
{
    return kZeroResources;
}

size_t WaterInterface::getId() 
{
    return static_cast<size_t>(ReservedTypes::WATER);
}

#include "../../Standart/Plugin.hpp"
CellInterface* getCellInterface()
{
    return new WaterInterface();
}