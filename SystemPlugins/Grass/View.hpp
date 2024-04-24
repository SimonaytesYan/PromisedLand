#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

static const char* kViewAsset = "Assets/Grass.png";

class GrassView : public CellView
{
public:
    explicit GrassView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI(kViewAsset), pos, parent)
    {}
};