#pragma once

#include "GameObject.hpp"
#include "Resources.hpp"

class Cell : GameObject 
{
public:

    explicit Cell(const size_t _field_type)
      :  field_type (_field_type)
    {}

    virtual size_t getFieldType() const 
    {
        return field_type;
    }

protected:
    size_t field_type;
};