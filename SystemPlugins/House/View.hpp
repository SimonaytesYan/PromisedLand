#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class HouseView : public CellView
{
public:
    explicit HouseView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI("Assets/House.png"), pos, parent)
    {}
};