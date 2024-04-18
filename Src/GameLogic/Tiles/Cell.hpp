#pragma once

#include "../GameObject.hpp"
#include "../Resources.hpp"

enum class FieldType;

class Cell : GameObject 
{
public:
    static Cell* createInstance(const FieldType field_type);

    explicit Cell() = default;

    virtual FieldType getFieldType() const = 0;
};