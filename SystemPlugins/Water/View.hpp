#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class WaterView : public CellView
{
public:
    explicit WaterView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI("Assets/Water.png"), pos, parent)
    {}
};