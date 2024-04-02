#pragma once

#include <functional>

#include "../GameObject.h"

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

protected:
    Function func;
    void*    args;
};

class Button : GameObject
{
public:
    Button(int x, int y, size_t x_len, size_t y_len, const Functor& func, 
           const char* imp_path) :
    GameObject       (x, y),
    x_len            (x_len),
    y_len            (y_len),
    on_click         (func),
    texture          (imp_path)
    { }
    
    void draw(RenderTarget& render_target)
    {
        render_target.drawTexture(x, y, texture);
    }

    bool onClick(int press_x, int press_y)
    {
        if (x <= press_x && press_x <= x + x_len &&
            y <= press_y && press_y <= y + y_len)
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
