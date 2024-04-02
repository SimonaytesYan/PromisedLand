#pragma once

#define BUILDING(name, building_res, tick_res, texture_path)    \
    class name : public Building                                \
    {                                                           \
    public:                                                     \
        name(int x, int y) : Building(x, y)                     \
        { }                                                     \
                                                                \
        Resources getBuildingIncome() override                  \
        { return building_res; }                                \
                                                                \
        Resources getTickIncome() override                      \
        { return tick_res; }                                    \
                                                                \
        void draw(RenderTarget& render_target) override         \
        {                                                       \
            static Texture texture(texture_path);               \
            render_target.drawTexture(x, y, texture);           \
        }                                                       \
    }; 
