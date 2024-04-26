#pragma once

#include "../../Standart/CellInterface.hpp"

class WaterInterface : public CellInterface
{
public:
    CellType    getType        ()                                                 override;
    Cell*       createCell     ()                                                 override;
    CellView*   createCellView (const Point pos, CellViewGroupI& cell_view_group) override;
    Bitmask     getBuildMask   ()                                                 override;
    Resources   getAppearIncome()                                                 override;
    size_t      getId          ()                                                 override;
    const char* getAsset       ()                                                 override;
};