#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class GrassView : public CellView
{
public:
    explicit GrassView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI("Assets/Grass.png"), pos, parent)
    {}
};