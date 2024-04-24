#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

HouseCell::HouseCell()
  :  Building (static_cast<size_t>(ReservedTypes::HOUSE), 0)
{}

Resources HouseCell::getAppearIncome() const
{
  return Resources( 0,  0, -15, 5,  5, 0);
}

Resources HouseCell::getTickIncome() const
{
  return Resources(-5, -5, 0, 0, 0, 0);
}

Resources HouseCell::getDestroyIncome() const
{
  return Resources(0, 0, 10, -5, -5, 0);
}

Bitmask HouseCell::getBuildMask() const
{
  return ~((1 << 1) | (1 << 2) | (1 << 3));
}
