#pragma once

#include "Resources.hpp"

using FieldType = size_t;

class Cell : GameObject 
{
public:

    explicit Cell(const FieldType _field_type)
      :  field_type (_field_type)
    {}

    virtual FieldType getFieldType() const 
    {
        return field_type;
    }

protected:
    FieldType field_type;
};