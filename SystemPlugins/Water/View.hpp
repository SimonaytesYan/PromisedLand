#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class WaterView : public CellView
{
public:
    explicit WaterView(const Point pos, CellViewGroup& parent)
      :  CellView (Texture("Assets/Water.png"), pos, parent)
    {}
};