#pragma once

#include "../GameObject.h"
#include "../Resources.h"
#include "../ResourcesManager.h"
#include "TextView.hpp"

class ResourceBar : public GameObject
{
public:
    // TODO: bad constant
    explicit ResourceBar(const int width, const int y_start, ResourcesManager& _resource_manager)
      : food_view        (0            , y_start),
        water_view       (width / 4    , y_start),
        wood_view        (width / 2    , y_start),
        population_view  (width / 4 * 3, y_start),
        resource_manager (_resource_manager)       
    {
        updateValues(resource_manager.getUserRes());
    }

    void draw(RenderTarget& render_target) override
    {
        food_view      .draw(render_target);
        water_view     .draw(render_target);
        wood_view      .draw(render_target);
        population_view.draw(render_target);
    }

    bool onClick(int x, int y) override {}
    void onTick()              override 
    { updateValues(resource_manager.getUserRes()); }

private:

    void updateValues(const Resources resources)
    {
        food_view      .setContent("Food: "   + std::to_string(resources.food));
        water_view     .setContent("Water: "  + std::to_string(resources.water));
        wood_view      .setContent("Wood: "   + std::to_string(resources.wood));
        population_view.setContent("People: " + std::to_string(resources.population));
    }

private:
    // TODO: make better
    TextView food_view;
    TextView water_view;
    TextView wood_view;
    TextView population_view;

    ResourcesManager& resource_manager;
};