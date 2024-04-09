#pragma once

#include "Building.hpp"
#include "../../../Constants.hpp"
#include "../Resources.hpp"

#define CELL_LOGIC(name, base_class, appear_res, tick_res)  \
    class name : public base_class                          \
    {                                                       \
    public:                                                 \
        name() : base_class()                               \
        { }                                                 \
                                                            \
        Resources getAppearIncome() override                \
        { return appear_res; }                              \
                                                            \
        Resources getTickIncome() override                  \
        { return tick_res; }                                \
    }; 


CELL_LOGIC(Grass,    Cell    , Resources( 0,  0,   0, 0, 0), Resources( 0,  0, 0, 0, 0))
CELL_LOGIC(Water,    Cell    , Resources( 0,  0,   0, 0, 0), Resources( 0,  0, 0, 0, 0))
CELL_LOGIC(House,    Building, Resources( 0,  0, -15, 5, 0), Resources(-5, -5, 0, 0, 0))
CELL_LOGIC(Sawmill,  Building, Resources( 0,  0, -10, 0, 0), Resources( 0,  0, 2, 0, 0))
CELL_LOGIC(Well,     Building, Resources( 0,  0, -10, 0, 0), Resources( 0, 10, 0, 0, 0))
CELL_LOGIC(Windmill, Building, Resources( 0,  0, -10, 0, 0), Resources(10,  0, 0, 0, 0))
