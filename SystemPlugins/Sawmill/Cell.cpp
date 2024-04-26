#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

SawmillCell::SawmillCell()
  :  Building (static_cast<size_t>(ReservedTypes::SAWMILL), 5)
{}

Resources SawmillCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources SawmillCell::getTickIncome()
{
  return kTickIncome;
}

Resources SawmillCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask SawmillCell::getBuildMask() const
{
  return kBuildMask;
}
