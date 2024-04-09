#pragma once

#include "../../Constants.hpp"
#include "../Logics/Tiles/Cell.hpp"
#include "../Logics/Tiles/CellCreator.hpp"
#include "../Events/ResourceEvent.hpp"
#include "ResourceManager.hpp"
#include "ViewManager.hpp"

class CellViewManager : public ViewManager
{
public:
    explicit CellViewManager(const FieldType _field_type, ResourceManager& _res_manager)
      : res_manager (_res_manager),
        cell        (nullptr)
    {
        switch (_field_type)
        {
        case FieldType::Grass:
            cell = new Grass();
            break;
        case FieldType::Water:
            cell = new Water();
            break;
        case FieldType::House:
            cell = new House();
            break;
        case FieldType::Sawmill:
            cell = new Sawmill();
            break;
        case FieldType::Well:
            cell = new Well();
            break;
        case FieldType::Windmill:
            cell = new Windmill();
            break;
        default:
            break;
        }

        res_manager.addCell(cell);
    }

    void pushToLogic(const Event* event) override
    {
        switch (event->event_type)
        {
        case EventType::TICK:
          {  
            ResourceEvent res_event(EventType::TICK, cell->getTickIncome());
            res_manager.pushToLogic(&res_event);
            break;
          }
        case EventType::MOUSE_CLICK:
            break;
        default:
            break;
        }
    }

private:
    ResourceManager& res_manager;
    Cell*            cell;
};