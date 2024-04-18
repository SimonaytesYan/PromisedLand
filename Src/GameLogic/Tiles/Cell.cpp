#include "Cell.hpp"
#include "../../Constants.hpp"
#include "CellCreator.hpp"

#define CELL_LOGIC(name)  \
    case FieldType::name:                       \
        return new name();

#define BUILDING_LOGIC(name, ...) CELL_LOGIC(name)

Cell* Cell::createInstance(const FieldType field_type)
{
    switch (field_type)
    {
        #include "../../GameLogic/Tiles/CellPreforms.hpp"
        #include "../../GameLogic/Tiles/BuildingPreforms.hpp"

        default:
            return nullptr;
    }
}
