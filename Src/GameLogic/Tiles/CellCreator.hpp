#pragma once

#include "Building.hpp"
#include "../../Constants.hpp"
#include "../Resources.hpp"

#define CELL_LOGIC(name)                \
    class name : public Cell            \
    {                                   \
    public:                             \
        name() : Cell()                 \
        { }                             \
    }; 

#define BUILDING_LOGIC(name, max_workers, appear_res, tick_res, destroy_res)          \
    class name : public Building                                                      \
    {                                                                                 \
    public:                                                                           \
        name() : Building(max_workers)                                                \
        { }                                                                           \
                                                                                      \
        Resources getAppearIncome() const override                                    \
        { return appear_res; }                                                        \
                                                                                      \
        Resources getTickIncome() const override                                      \
        { return tick_res; }                                                          \
                                                                                      \
        Resources getDestroyIncome() const override                                   \
        { return destroy_res; }                                                       \
    }; 


CELL_LOGIC(Grass)
CELL_LOGIC(Water)

BUILDING_LOGIC(House,     5, Resources( 0,  0, -15, 5,  5), Resources(-5, -5, 0, 0, 0), Resources(0, 0, 10, -5, -5))
BUILDING_LOGIC(Sawmill,  20, Resources( 0,  0, -10, 0, -2), Resources( 0,  0, 2, 0, 0), Resources(0, 0,  7,  0,  2))
BUILDING_LOGIC(Well,      2, Resources( 0,  0, -10, 0, -2), Resources( 0, 10, 0, 0, 0), Resources(0, 0,  7,  0,  2))
BUILDING_LOGIC(Windmill,  5, Resources( 0,  0, -10, 0, -2), Resources(10,  0, 0, 0, 0), Resources(0, 0,  7,  0,  2))
