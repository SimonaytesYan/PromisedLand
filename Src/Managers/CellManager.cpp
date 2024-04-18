#include "CellManager.hpp"
#include "../Interlayers/CellInterlayer.hpp"

void CellManager::createCell(const Point position)
{
    Cell* new_cell = nullptr;

    switch (cell_type)
    {
    case FieldType::Grass:
        new_cell = new Grass();
        break;
    case FieldType::Water:
        new_cell = new Water();
        break;
    case FieldType::House:
      {
        new_cell = new House();
        cell_interlayer->pushToLogic(new NewCitizensEvent(static_cast<House*>(new_cell)->getAppearIncome().population));

        break;
      }
    case FieldType::Sawmill:
        new_cell = new Sawmill();
        break;
    case FieldType::Well:
        new_cell = new Well();
        break;
    case FieldType::Windmill:
        new_cell = new Windmill();
        break;
    case FieldType::FieldNumber:
    case FieldType::Error:
        break;
    default:
        break;
    }

    createCell(new_cell);
    res_manager->onBuild(new_cell);
}