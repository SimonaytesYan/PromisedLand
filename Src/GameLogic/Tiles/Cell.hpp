#pragma once

#include "../GameObject.hpp"
#include "../Resources.hpp"

enum class FieldType;

class Cell : GameObject 
{
public:
    explicit Cell() = default;

    virtual FieldType getFieldType() = 0;
};