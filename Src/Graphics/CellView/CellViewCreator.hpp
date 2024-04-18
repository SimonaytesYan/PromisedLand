#pragma once

#include "CellView.hpp"

static const char* kCellsAssets[] = {"Assets/field.png",
                                     "Assets/water.png",
                                     "Assets/Forest.png",
                                     "Assets/house.png",
                                     "Assets/sawmill.png",
                                     "Assets/well.png",
                                     "Assets/windmill.png"};

#define CELL_VIEW(name, texture_path, field_type)                     \
    class name : public CellView                                      \
    {                                                                 \
    public:                                                           \
        name (Point pos, CellViewGroup& parent) :                     \
        CellView (Texture(texture_path), pos, parent)                 \
        { }                                                           \
    };

CELL_VIEW(GrassView,    kCellsAssets[0], FieldType::Grass);
CELL_VIEW(WaterView,    kCellsAssets[1], FieldType::Water);
CELL_VIEW(ForestView,   kCellsAssets[2], FieldType::Forest);
CELL_VIEW(HouseView,    kCellsAssets[3], FieldType::House);
CELL_VIEW(SawmillView,  kCellsAssets[4], FieldType::Sawmill);
CELL_VIEW(WellView,     kCellsAssets[5], FieldType::Well);
CELL_VIEW(WindmillView, kCellsAssets[6], FieldType::Windmill);
