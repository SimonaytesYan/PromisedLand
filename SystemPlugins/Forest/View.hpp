#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class ForestView : public CellView
{
public:
    explicit ForestView(const Point pos, CellViewGroupI& parent)
      :  CellView (Texture("Assets/Forest.png"), pos, parent)
    {}
};