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

CELL_VIEW(Grass,    kCellsAssets[0]);
CELL_VIEW(Water,    kCellsAssets[1]);
CELL_VIEW(House,    kCellsAssets[2]);
CELL_VIEW(Sawmill,  kCellsAssets[3]);
CELL_VIEW(Well,     kCellsAssets[4]);
CELL_VIEW(Windmill, kCellsAssets[5]);
