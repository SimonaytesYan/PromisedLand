#pragma once

#include <iostream>

#include "Field/Field.h"
#include "Resources.h"
#include "EventProcessable.h"
#include "BuildManager/BuildingManager.h"
#include "../StlVector/Src/Vector.hpp"

// Every tick update resources from fields
// Kill program if population less then zero
class ResourcesManager : public GameObject
{    
public:
    explicit ResourcesManager(Resources start_resources, BuildingManager* build_manager) 
      : user_res     (start_resources), 
        build_manager(build_manager) {}


    void draw(RenderTarget& render_target)
    {
        const size_t field_num = fields.Size();
        for (size_t i = 0; i < field_num; i++)
            fields[i]->draw(render_target);
    }

    bool onClick(int x, int y) override 
    {
        printf("ResourcesManager::OnClock(%d %d)\n", x, y);

        const size_t field_num = fields.Size();
        for (size_t i = 0; i < field_num; i++)
        {
            const bool res = fields[i]->onClick(x, y);
            if (res)
            {
                printf("ResourcesManager find field %d\n", i);
                if (build_manager->FieldTypeSetted())
                {
                    printf("ResourcesManager build_manager field setted%d\n", i);
                    const int new_x = fields[i]->getX();
                    const int new_y = fields[i]->getY();
                    Field* new_field;

                    switch (build_manager->getFieldType())
                    {
                        case FieldType::Grass:
                            new_field = new Grass(new_x, new_y);
                            break;
                        case FieldType::House:
                            new_field = new House(new_x, new_y);
                            break;
                        case FieldType::Sawmill:
                            new_field = new Sawmill(new_x, new_y);
                            break;
                        case FieldType::Well:
                            new_field = new Well(new_x, new_y);
                            break;
                        case FieldType::Windmill:
                            new_field = new Windmill(new_x, new_y);
                            break;

                        default:
                            break;
                    }

                    delete fields[i];
                    fields[i] = new_field;
                }
                return true;
            }
        }

        return false;
    }

    void onTick() override 
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
    BuildingManager* const build_manager;
    Resources              user_res;
    Vector<Field*>         fields;
};
