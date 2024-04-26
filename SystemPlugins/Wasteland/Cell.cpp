#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

WastelandCell::WastelandCell()
  :  Building (static_cast<size_t>(ReservedTypes::WASTELAND), 0)
{}

Resources WastelandCell::getAppearIncome() const
{
  return kAppearIncome;
}

Resources WastelandCell::getTickIncome()
{
  return kTickIncome;
}

Resources WastelandCell::getDestroyIncome() const
{
  return kDestroyIncome;
}

Bitmask WastelandCell::getBuildMask() const
{
  return kBuildMask;
}
