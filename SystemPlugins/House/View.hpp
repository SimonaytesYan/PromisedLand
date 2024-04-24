#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class HouseView : public CellView
{
public:
    explicit HouseView(const Point pos, CellViewGroup& parent)
      :  CellView (Texture("Assets/House.png"), pos, parent)
    {}
};