#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

static const char* kViewAsset = "Assets/Forest.png";

class ForestView : public CellView
{
public:
    explicit ForestView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI(kViewAsset), pos, parent)
    {}
};