#include "CellManager.hpp"
#include "../Interlayers/CellInterlayer.hpp"

void CellManager::createCell(const Point position)
{
    Cell*     new_cell      = nullptr;
    CellView* new_view_cell = nullptr;

    switch (cell_type)
    {
    case FieldType::Grass:
        new_cell      = new Grass();
        new_view_cell = new GrassView(position, *cell_interlayer);
        break;
    case FieldType::Water:
        new_cell      = new Water();
        new_view_cell = new WaterView(position, *cell_interlayer);
        break;
    case FieldType::House:
      {
        new_cell      = new House();
        new_view_cell = new HouseView(position, *cell_interlayer);

        cell_interlayer->pushToLogic(new NewCitizensEvent(static_cast<House*>(new_cell)->getAppearIncome().population));

        break;
      }
    case FieldType::Sawmill:
        new_cell      = new Sawmill();
        new_view_cell = new SawmillView(position, *cell_interlayer);
        break;
    case FieldType::Well:
        new_cell      = new Well();
        new_view_cell = new WellView(position, *cell_interlayer);
        break;
    case FieldType::Windmill:
        new_cell      = new Windmill();
        new_view_cell = new WindmillView(position, *cell_interlayer);
        break;
    case FieldType::FieldNumber:
    case FieldType::Error:
        break;
    default:
        break;
    }

    createCell(new_cell);
    res_manager->onBuild(new_cell);

    cell_interlayer->pushToView(new CreateCellViewEvent(new_view_cell));
}