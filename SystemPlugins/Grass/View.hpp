#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class GrassView : public CellView
{
public:
    explicit GrassView(const Point pos, CellViewGroup& parent)
      :  CellView (Texture("Assets/Grass.png"), pos, parent)
    {}
};