#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

WaterTowerCell::WaterTowerCell()
  :  Building (static_cast<size_t>(ReservedTypes::WATER_TOWER), 2)
{}

Resources WaterTowerCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources WaterTowerCell::getTickIncome()
{
  return kTickIncome;
}

Resources WaterTowerCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask WaterTowerCell::getBuildMask() const
{
  return kBuildMask;
}
