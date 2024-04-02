#pragma once

#define FIELD(name, appear_res, tick_res, texture_path)          \
    class name : public Field                                   \
    {                                                           \
    public:                                                     \
        name(int x, int y) : Field(x, y)                        \
        { }                                                     \
                                                                \
        Resources getAppearIncome() override                    \
        { return appear_res; }                                \
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
