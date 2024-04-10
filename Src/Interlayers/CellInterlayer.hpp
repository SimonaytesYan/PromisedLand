#pragma once

#include "../../StlVector/Src/Vector.hpp"
#include "ViewInterlayer.hpp"
#include "LogicInterlayer.hpp"
#include "../Graphics/CellView/CellViewCreator.hpp"
#include "../Managers/CellManager.hpp"

class Window;

class CellInterlayer : public ViewInterlayer, public LogicInterlayer
{
public:
    // explicit CellInterlayer(CellManager& cell_manager, 
    //                         const Vector<CellView*>& cell_views)
    //   : cell_manager (cell_manager),
    //     cell_views   (cell_views)
    // { }

    explicit CellInterlayer(CellManager& cell_manager)
      : cell_manager (cell_manager),
        cell_views   (),
        window       (nullptr)
    { }

    void setWindow(Window* _window)
    {
        window = _window;
    }

    void pushToView(const Event* event) override;

    void pushToLogic(const Event* event) override
    {
        printf("INSIDE\n");
        printf("%d\n", event->event_type);
        switch (event->event_type)
        {
        case EventType::TICK:
            printf("TO CELL\n");
            cell_manager.onTick();
            break;
        case EventType::MOUSE_CLICK:
          {
            const MouseEvent* mouse_event = static_cast<const MouseEvent*>(event);
            cell_manager.createCell(mouse_event->pos);
            break;
          }
        default:
            break;
        }
    }

private:
    Vector<CellView*> cell_views;   // CellInterlayer don`t own it
    CellManager&      cell_manager;
    Window*           window;
};