#include "Building.hpp"
#include "../../Constants.hpp"

#define BUILDING_LOGIC(name, build_mask, ...)    \
    case FieldType::name:                        \
        return build_mask;

Bitmask Building::getBuildMask(FieldType field_type)
{
    switch (field_type)
    {
        #include "BuildingPreforms.hpp"    
    
        default:
            return 0;
    }

    return 0;
}

#undef BUILDING_LOGIC