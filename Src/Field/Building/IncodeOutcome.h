#pragma once

#define HOUSE_BUILDING    Resources( 0,  0, -15, 5)
#define WELL_BUILDING     Resources( 0,  0, -10, 0)
#define WINDMILL_BUILDING Resources( 0,  0, -10, 0)
#define SAWMILL_BUILDING  Resources( 0,  0, -10, 0)

#define HOUSE_TICK    Resources(-5, -5, 0, 0)
#define WELL_TICK     Resources( 0, 20, 0, 0)
#define WINDMILL_TICK Resources(20,  0, 0, 0)
#define SAWMILL_TICK  Resources( 0,  0, 2, 0)

#define BUILDING(name, building_res, tick_res, color)           \
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
            render_target.drawCircle(x, y, kFieldSize, color);  \
        }                                                       \
    }; 
