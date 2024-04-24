#pragma once

#include "../../Standart/CellInterface.hpp"

class GrassInterface : public CellInterface
{
public:
    CellType  getType        ()                                                override;
    Cell*     createCell     ()                                                override;
    CellView* createCellView (const Point pos, CellViewGroup& cell_view_group) override;
    Bitmask   getBuildMask   ()                                                override;
    Resources getAppearIncome()                                                override;
    size_t    getId          ()                                                override;
};