#pragma once

#include <vector>

#include "ViewInterlayer.hpp"
#include "LogicInterlayer.hpp"
#include "../Graphics/CellView/CellViewCreator.hpp"
#include "../Managers/CellManager.hpp"

class Window;

class CellInterlayer : public ViewInterlayer, public LogicInterlayer
{
public:
    explicit CellInterlayer(CellManager& cell_manager)
      : cell_manager (cell_manager),
        cell_views   (),
        window       (nullptr)
    { }

    void setWindow(Window* _window)
    {
        window = _window;
    }

    void pushToView(const Event* event)  override;
    void pushToLogic(const Event* event) override;

private:
    std::vector<CellView*> cell_views;   // CellInterlayer don`t own it
    CellManager&           cell_manager;
    Window*                window;
};