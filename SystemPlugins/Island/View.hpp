#pragma once

#include "../../Standart/Graphics/CellView/CellView.hpp"

class IslandView : public CellView
{
public:
    explicit IslandView(const Point pos, CellViewGroup& parent)
      :  CellView (Texture("Assets/Island.png"), pos, parent)
    {}
};