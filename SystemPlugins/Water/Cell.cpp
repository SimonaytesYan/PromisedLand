#include "Cell.hpp"
#include "../../Standart/CellInterface.hpp"

WaterCell::WaterCell()
  :  Cell (static_cast<size_t>(ReservedTypes::WATER))
{}
