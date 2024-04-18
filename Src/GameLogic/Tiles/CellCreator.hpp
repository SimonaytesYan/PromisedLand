#pragma once

#include "Building.hpp"
#include "../../Constants.hpp"
#include "../Resources.hpp"

#define CELL_LOGIC(name)                        \
    class name : public Cell                    \
    {                                           \
    public:                                     \
        name() : Cell()                         \
        { }                                     \
                                                \
        FieldType getFieldType() const override \
        { return FieldType::name; }             \
    }; 

#define BUILDING_LOGIC(name, build_mask, max_workers, appear_res, tick_res, destroy_res)    \
    class name : public Building                                                \
    {                                                                           \
    public:                                                                     \
        name() : Building(max_workers)                                          \
        { }                                                                     \
                                                                                \
        Resources getAppearIncome() const override                              \
        { return appear_res; }                                                  \
                                                                                \
        Resources getTickIncome() const override                                \
        { return tick_res; }                                                    \
                                                                                \
        Resources getDestroyIncome() const override                             \
        { return destroy_res; }                                                 \
                                                                                \
        FieldType getFieldType() const override                                 \
        { return FieldType::name; }                                             \
                                                                                \
        Bitmask getBuildMask() const override                                   \
        { return build_mask; }                                                  \
    };

#include "CellPreforms.hpp"
#include "BuildingPreforms.hpp"

#undef CELL_LOGIN
#undef BUILDING_LOGIC