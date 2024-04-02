#include "Window.h"

const sf::Color kBackgroundColor(128, 255, 255);

void Window::draw(RenderTarget& render_target)
{
    render_target.drawRect(x, y, x_size, y_size, kBackgroundColor);

    const size_t child_num = child.size();
    for (size_t i = 0; i < child_num; i++)
        child[i]->draw(render_target);
}

void Window::onClick(int click_x, int click_y)
{
    const size_t child_num = child.size();
    for (size_t i = 0; i < child_num; i++)
        child[i]->onClick(click_x, click_y);
}

void Window::onTick()
{
    const size_t child_num = child.size();
    for (size_t i = 0; i < child_num; i++)
        child[i]->onTick();    
}

void Window::addChild(GameObject* new_game_object)
{
    child.push_back(new_game_object);
}

Window::~Window()
{
    for (size_t i = 0; i < child.size(); ++i)
    {
        delete child[i];
    }
}