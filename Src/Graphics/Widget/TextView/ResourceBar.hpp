#pragma once

#include "../../Eventable.hpp"
#include "../../Renderable.hpp"
#include "../../Managers/ResourceManager.hpp"
#include "../../Logics/Resources.hpp"
#include "TextView.hpp"

class ResourceBar : public Eventable, public Renderable
{
public:
    explicit ResourceBar(const int width, const int y_start, ResourceManager& _resource_manager)
      : food_view        ({0            , y_start}),
        water_view       ({width / text_view_cnt    , y_start}),
        wood_view        ({width / text_view_cnt * 2, y_start}),
        population_view  ({width / text_view_cnt * 3, y_start}),
        free_pop_view    ({width / text_view_cnt * 4, y_start}),
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
        free_pop_view  .draw(render_target);
    }

    void push(const Event* event) override
    {
        switch (event->event_type)
        {
        case EventType::TICK:
            updateValues(resource_manager.getUserRes());
            break;
        case EventType::MOUSE_CLICK:
            break;
        default:
            break;
        }
    }

private:

    void updateValues(const Resources resources)
    {
        food_view      .setContent(kFoodTitle       + std::to_string(resources.food));
        water_view     .setContent(kWaterTitle      + std::to_string(resources.water));
        wood_view      .setContent(kWoodTitle       + std::to_string(resources.wood));
        population_view.setContent(kPopulationTitle + std::to_string(resources.population));
        free_pop_view  .setContent(kFreePopTitle    + std::to_string(resources.free_population));
    }

    const int text_view_cnt = 5;

    const char* kFoodTitle       = "Food: ";
    const char* kWaterTitle      = "Water: ";
    const char* kWoodTitle       = "Wood: ";
    const char* kPopulationTitle = "People: ";
    const char* kFreePopTitle    = "Free people: ";

private:
    // TODO: make better
    TextView food_view;
    TextView water_view;
    TextView wood_view;
    TextView population_view;
    TextView free_pop_view;

    ResourceManager& resource_manager;
};