#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class IslandView : public CellView
{
public:
    explicit IslandView(const Point pos, CellViewGroupI& parent)
      :  CellView (TextureI("Assets/Island.png"), pos, parent)
    {}
};