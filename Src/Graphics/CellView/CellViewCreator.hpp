#pragma once

#include "CellView.hpp"

const char* kCellsAssets[] = {"Assets/field.png",
                              "Assets/water.png",
                              "Assets/house.png",
                              "Assets/sawmill.png",
                              "Assets/well.png",
                              "Assets/windmill.png"};

#define CELL_VIEW(name, texture_path)               \
    class name : CellView                           \
    {                                               \
        name (const int x = 0, const int y = 0) :   \
        CellView (Texture(texture_path), x, y)      \
        { }                                         \
    };

CELL_VIEW(GrassView,    kCellsAssets[0]);
CELL_VIEW(WaterView,    kCellsAssets[1]);
CELL_VIEW(HouseView,    kCellsAssets[2]);
CELL_VIEW(SawmillView,  kCellsAssets[3]);
CELL_VIEW(WellView,     kCellsAssets[4]);
CELL_VIEW(WindmillView, kCellsAssets[5]);
