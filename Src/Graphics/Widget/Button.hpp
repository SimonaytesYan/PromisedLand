#pragma once

#include <functional>

#include "Widget.hpp"

typedef void (*Function)(void* args);

class Functor
{
public:
    Functor(Function function, void* args) :
    func(function),
    args(args)
    { }

    void operator()()
    {
        func(args);
    }

    ~Functor()
    { }

protected:
    Function func;
    void*    args;
};

class Button : public Widget
{
public:
    Button(int x, int y, size_t x_len, size_t y_len, const Functor& func, 
           const char* imp_path) :
    Widget   (x, y),
    x_len    (x_len),
    y_len    (y_len),
    on_click (func),
    texture  (imp_path)
    { }
    
    void draw(RenderTarget& render_target)
    {
        render_target.drawTexture(point, texture);
    }

    bool onClick(int press_x, int press_y)
    {
        printf("Button::onClick(%d %d)\n", point.x, point.y);
        if (point.x <= press_x && press_x <= point.x + x_len &&
            point.y <= press_y && press_y <= point.y + y_len)
        {
            on_click();
            return true;
        }
        return false;
    }

    void onTick()
    { }

private:
    size_t  x_len;
    size_t  y_len;
    Texture texture;
    Functor on_click;
};
