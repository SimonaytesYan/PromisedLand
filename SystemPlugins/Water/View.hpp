#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

static const char* kViewAsset = "Assets/Water.png";

class WaterView : public CellView
{
public:
    explicit WaterView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI(kViewAsset), pos, parent)
    {}
};