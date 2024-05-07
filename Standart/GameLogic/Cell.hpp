#pragma once

#include "Resources.hpp"

using FieldType = size_t;

class Cell : GameObject 
{
public:

    explicit Cell(const FieldType _field_type)
      :  field_type (_field_type),
         index      (0)
    {}


    virtual FieldType getFieldType() const 
    {
        return field_type;
    }

    virtual void setIndexInCellGroup(size_t _index) 
    {
        index = _index;
    }

    virtual size_t getIndex()
    {
        return index;
    }

protected:
    FieldType field_type;
    size_t    index;
};