#pragma once

#include "CellView.hpp"

#define CREATE_STRING(str) #str
#define GET_ASSERT_PATH(name) CREATE_STRING(Assets/name.png)

#define CELL_LOGIC(name)          GET_ASSERT_PATH(name),
#define BUILDING_LOGIC(name, ...) GET_ASSERT_PATH(name),

static const char* kCellsAssets[] = {
    #include "../../GameLogic/Tiles/CellPreforms.hpp"
    #include "../../GameLogic/Tiles/BuildingPreforms.hpp"
};

#undef CELL_LOGIC
#undef BUILDING_LOGIC

#define CELL_LOGIC(name)                                              \
    class name##View : public CellView                                \
    {                                                                 \
    public:                                                           \
        name##View (Point pos, CellViewGroup& parent) :               \
        CellView (Texture(GET_ASSERT_PATH(name)), pos, parent)        \
        { }                                                           \
    };

#define BUILDING_LOGIC(name, ...) CELL_LOGIC(name)

#include "../../GameLogic/Tiles/CellPreforms.hpp"
#include "../../GameLogic/Tiles/BuildingPreforms.hpp"

#undef CELL_LOGIC
#undef BUILDING_LOGIC
