#pragma once

#include "../../Standart/CellInterface.hpp"

static const char* kViewAsset = "Assets/Grass.png";

class GrassInterface : public CellInterface
{
public:
    CellType    getType        () override;
    Cell*       createCell     () override;
    Bitmask     getBuildMask   () override;
    Resources   getAppearIncome() override;
    size_t      getId          () override;
    const char* getAsset       () override;
};