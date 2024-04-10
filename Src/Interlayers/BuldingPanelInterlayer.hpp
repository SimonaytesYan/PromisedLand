#pragma once

#include "ViewInterlayer.hpp"
#include "../Managers/CellManager.hpp"

class BuildingPanelInterlayer : ViewInterlayer
{
public:
    BuildingPanelInterlayer(CellManager& cell_manager) :
    cell_manager (cell_manager)
    {}

    void pushToLogic(const Event* event) override
    {
        
    }

private:
    CellManager& cell_manager;
};