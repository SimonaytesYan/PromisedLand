#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

HouseCell::HouseCell()
  :  Building (static_cast<size_t>(ReservedTypes::HOUSE), 0)
{}

Resources HouseCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources HouseCell::getTickIncome() const
{
  return kTickIncome;
}

Resources HouseCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask HouseCell::getBuildMask() const
{
  return kBuildMask;
}
