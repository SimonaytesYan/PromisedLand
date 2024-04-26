#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

WindmillCell::WindmillCell()
  :  Building (static_cast<size_t>(ReservedTypes::WINDMILL), 2)
{}

Resources WindmillCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources WindmillCell::getTickIncome() const
{
  return kTickIncome;
}

Resources WindmillCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask WindmillCell::getBuildMask() const
{
  return kBuildMask;
}
