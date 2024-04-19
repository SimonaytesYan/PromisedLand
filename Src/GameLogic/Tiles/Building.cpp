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


#define BUILDING_LOGIC(name, build_mask, max_workers, appear_res, ...)    \
    case FieldType::name:                                                 \
        return appear_res;

Resources Building::getAppearIncome(FieldType field_type)
{
    switch (field_type)
    {
        #include "BuildingPreforms.hpp"    
    
        default:
            return kZeroResources;
    }

    return kZeroResources;
}

#undef BUILDING_LOGIC
