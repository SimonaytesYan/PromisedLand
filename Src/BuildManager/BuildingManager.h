#pragma once
#include "../Field/Field.h"
#include "../Field/Fields.h"

class BuildingManager
{
public:

    BuildingManager() :
    current (FieldType::Error)
    {}

    void setFieldType(FieldType building)
    { 
        printf("setFieldType = %d\n", building);
        current = building; 
    }

    FieldType getFieldType()
    { return current; }

    bool FieldTypeSetted()
    { return current != FieldType::Error; }

private:
    FieldType current;
};