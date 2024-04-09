#pragma once

#include "../Logics/Tiles/Cell.hpp"
#include "../../../StlVector/Src/VectorDecor.hpp"

class ResourceManager
{
public:
    explicit ResourceManager()
      : cells ()
    {}

    // Non-copyable
    ResourceManager(const ResourceManager& other)           = delete;
    ResourceManager operator=(const ResourceManager& other) = delete;

    // Non-movable
    ResourceManager(ResourceManager&& other)           = delete;
    ResourceManager operator=(ResourceManager&& other) = delete;

    ~ResourceManager()
    {
        STLVectorDecor<Cell*> vector_traits(cells);
        for (auto val : vector_traits)
        {
            delete val;
        }
    }

private:
    Vector<Cell*> cells;
};