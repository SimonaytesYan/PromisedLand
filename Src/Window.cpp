#include "Window.h"

const sf::Color kBackgroundColor(128, 255, 255);

void Window::draw(RenderTarget& render_target)
{
    // render_target.drawRect(x, y, x_size, y_size, kBackgroundColor);

    const size_t child_num = child.Size();
    for (size_t i = 0; i < child_num; i++)
        child[i]->draw(render_target);
}

bool Window::onClick(int click_x, int click_y)
{
    printf("Window::onClick(%d %d)\n", click_x, click_y);
    const size_t child_num = child.Size();
    for (size_t i = 0; i < child_num; i++) 
    {
        printf("child[%d]\n", i);
        bool res = child[i]->onClick(click_x, click_y);
        if (res)
            return true;
    }
    return false;
}

void Window::onTick()
{
    const size_t child_num = child.Size();
    for (size_t i = 0; i < child_num; i++)
        child[i]->onTick();    
}

void Window::addChild(GameObject* new_game_object)
{
    child.PushBack(new_game_object);
}

Window::~Window()
{
    for (size_t i = 0; i < child.Size(); ++i)
    {
        delete child[i];
    }
}