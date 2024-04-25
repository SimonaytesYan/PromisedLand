#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

WellCell::WellCell()
  :  Building (static_cast<size_t>(ReservedTypes::WELL), 2)
{}

Resources WellCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources WellCell::getTickIncome() const
{
  return kTickIncome;
}

Resources WellCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask WellCell::getBuildMask() const
{
  return kBuildMask;
}
