#pragma once

#include "../GameLogic/Tiles/Cell.hpp"
#include "../GameLogic/Tiles/CellCreator.hpp"
#include "ResourceManager.hpp"
#include "../../StlVector/Src/Vector.hpp"
#include "../Utils/Utils.hpp"

class CellManager
{
public:
    explicit CellManager(CellInterlayer* _cell_interlayer)
      : cells           (),
        res_manager     (nullptr),
        cell_interlayer (_cell_interlayer),
        cell_type       (FieldType::Error) 
    {}

    explicit CellManager(ResourceManager* _res_manager = nullptr, CellInterlayer* _cell_interlayer = nullptr)
      : cells           (),
        res_manager     (_res_manager),
        cell_interlayer (_cell_interlayer),
        cell_type       (FieldType::Error) 
    {}

    // Non-copyable
    CellManager(const CellManager& other)           = delete;
    CellManager operator=(const CellManager& other) = delete;

    // Non-movable
    CellManager(CellManager&& other)           = delete;
    CellManager operator=(CellManager&& other) = delete;

    ~CellManager()
    {
        for (size_t i = 0; i < cells.Size(); ++i)
        {
            delete cells[i];
        }
    }

    void setResourceManager(ResourceManager* _res_manager)
    {
        res_manager = _res_manager;
    }

    void setCellInterlayer(CellInterlayer* _cell_interlayer)
    {
        cell_interlayer = _cell_interlayer;
    }

    void setCellType(const FieldType _cell_type)
    {
        cell_type = _cell_type;
    }

    void onTick()
    {
        res_manager->onTick();
    }

    void createCell()
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
            new_cell = new House();
            break;
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
    }

    void deleteCell(Cell* delete_cell)
    {
        auto begin_iterator = cells.Begin();
        auto end_iterator   = cells.End();
        
        for (; begin_iterator != end_iterator; ++begin_iterator)
        {
            if (*begin_iterator == delete_cell)
            {
                res_manager->onDelete(delete_cell);
                cells.Erase(begin_iterator);
                return;
            }
        }
    }

private:
    void createCell(Cell* new_cell)
    {
        cells.PushBack(new_cell);
    }

private:
    Vector<Cell*>    cells;
    ResourceManager* res_manager;
    CellInterlayer*  cell_interlayer;
    FieldType        cell_type;
};
