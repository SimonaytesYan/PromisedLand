#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

OvenCell::OvenCell()
  :  Building (static_cast<size_t>(ReservedTypes::OVEN), 2)
{}

Resources OvenCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources OvenCell::getTickIncome()
{
  return kTickIncome;
}

Resources OvenCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask OvenCell::getBuildMask() const
{
  return kBuildMask;
}
