#pragma once

#include "../GameLogic/Tiles/Cell.hpp"
#include "ResourceManager.hpp"
#include "../../StlVector/Src/Vector.hpp"
#include "../Utils/Utils.hpp"

class CellManager
{
public:
    explicit CellManager()
      : cells       (),
        res_manager (nullptr) 
    {}

    explicit CellManager(ResourceManager* _res_manager)
      : cells       (),
        res_manager (_res_manager) 
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

    void createCell(Cell* new_cell)
    {
        cells.PushBack(new_cell);
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
    Vector<Cell*>    cells;
    ResourceManager* res_manager;
};
