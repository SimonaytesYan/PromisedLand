#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

static const char* kViewAsset = "Assets/Well.png";

class WellView : public CellView
{
public:
    explicit WellView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI(kViewAsset), pos, parent)
    {}
};