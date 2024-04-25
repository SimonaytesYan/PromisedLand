#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

static const char* kViewAsset = "Assets/Wasteland.png";

class WastelandView : public CellView
{
public:
    explicit WastelandView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI(kViewAsset), pos, parent)
    {}
};