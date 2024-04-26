#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

MineCell::MineCell()
  :  Building (static_cast<size_t>(ReservedTypes::MINE), 2)
{}

Resources MineCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources MineCell::getTickIncome() const
{
  return kTickIncome;
}

Resources MineCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask MineCell::getBuildMask() const
{
  return kBuildMask;
}
