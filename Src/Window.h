#pragma once

#include "GameObject.h"
// #include "../StlVector/Src/Vector.hpp"
#include <vector>

const size_t kDefaultWindowSize = 100;

class Window : public GameObject
{
public:
    Window() :
    GameObject(),
    x_size    (kDefaultWindowSize),
    y_size    (kDefaultWindowSize)
    { }

    Window(int x, int y, size_t x_size, size_t y_size) :
    GameObject(x, y),
    x_size    (x_size),
    y_size    (y_size)
    { }

    void addChild(GameObject* new_game_object);

    void draw(RenderTarget& render_target) override;
    void onClick(int x, int y) override;
    void onTick() override;

    ~Window();

private:
    size_t x_size;
    size_t y_size; 
    std::vector<GameObject*> child;
};
