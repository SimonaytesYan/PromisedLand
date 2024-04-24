#pragma once

#include "../../Standart/Graphics/CellView/CellViewI.hpp"

class ForestView : public CellViewI
{
public:
    explicit ForestView(const Point pos, CellViewGroup& parent)
      :  CellView (Texture("Assets/Forest.png"), pos, parent)
    {}
};