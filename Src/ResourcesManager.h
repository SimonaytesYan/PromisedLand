#pragma once

#include <iostream>

#include "Field/Field.h"
#include "Resources.h"
#include "EventProcessable.h"
#include "../StlVector/Src/Vector.hpp"

// Every tick update resources from fields
// Kill program if population less then zero
class ResourcesManager : public EventProcessable
{    
public:
    explicit ResourcesManager(Resources start_resources) 
      : user_res (start_resources) {}

    bool onClick(int x, int y) override { return false; }
    void onTick()              override 
    {  
        for (size_t i = 0; i < fields.Size(); ++i)
        {
            user_res += fields[i]->getTickIncome();
        }
    }

    Resources getUserRes()
    { return user_res; }

    void addField(Field* field) 
    { fields.PushBack(field); }

private:
    Resources      user_res;
    Vector<Field*> fields;
};
