#pragma once

#include "../../StlVector/Src/Vector.hpp"
#include "ViewInterlayer.hpp"
#include "LogicInterlayer.hpp"
#include "../Graphics/CellView/CellViewCreator.hpp"
#include "../Managers/CellManager.hpp"

class CellInterlayer : public ViewInterlayer, public LogicInterlayer
{
public:
    explicit CellInterlayer(CellManager& cell_manager, 
                            const Vector<CellView*>& cell_views)
      : cell_manager (cell_manager),
        cell_views   (cell_views)
    { }

    explicit CellInterlayer(CellManager& cell_manager)
      : cell_manager (cell_manager),
        cell_views   ()
    { }

    void pushToView(const Event* event) override
    {
        const size_t cell_views_size = cell_views.Size();
        for (size_t i = 0; i < cell_views_size; i++)
            cell_views[i]->push(event);
    }

    void pushToLogic(const Event* event) override
    {
        switch (event->event_type)
        {
        case EventType::TICK:
            cell_manager.onTick();
            break;
        case EventType::MOUSE_CLICK:
            cell_manager.createCell();
            break;
        default:
            break;
        }
    }

private:
    Vector<CellView*> cell_views;   // CellInterlayer don`t own it
    CellManager&      cell_manager;
};