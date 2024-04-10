#pragma once

#include "CellView.hpp"

const char* kCellsAssets[] = {"Assets/field.png",
                              "Assets/water.png",
                              "Assets/house.png",
                              "Assets/sawmill.png",
                              "Assets/well.png",
                              "Assets/windmill.png"};

#define CELL_VIEW(name, texture_path, field_type)                     \
    class name : CellView                                             \
    {                                                                 \
        name (Point pos, CellInterlayer& interlayer) :                \
        CellView (Texture(texture_path), pos, field_type, interlayer) \
        { }                                                           \
    };

CELL_VIEW(GrassView,    kCellsAssets[0], FieldType::Grass);
CELL_VIEW(WaterView,    kCellsAssets[1], FieldType::Water);
CELL_VIEW(HouseView,    kCellsAssets[2], FieldType::House);
CELL_VIEW(SawmillView,  kCellsAssets[3], FieldType::Sawmill);
CELL_VIEW(WellView,     kCellsAssets[4], FieldType::Well);
CELL_VIEW(WindmillView, kCellsAssets[5], FieldType::Windmill);
