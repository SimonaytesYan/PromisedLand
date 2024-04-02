#pragma once

#include <SFML/Graphics.hpp>

class RenderTarget
{
public:
    explicit RenderTarget(const int _x, const int _y);

    void setPixel   (const int x, const int y, const sf::Color color);
    void drawLine   (const int x1, const int y1, const int x2, const int y2, const sf::Color color);
    void drawRect   (const int x_lu, 
                     const int y_lu, 
                     const int x_size, 
                     const int y_size, 
                     const sf::Color fill_color,
                     const int line_thickness  = 0, 
                     const sf::Color out_color = sf::Color::Transparent);
    void drawEllipse(const int x_lu, const int y_lu, const int x_size, const int y_size, const sf::Color color);
    void drawText   (const int x, const int y, const char* const content, const uint16_t char_size, const sf::Color color);
    
    // void drawTexture(const int x_lu, const int y_lu, const int x_size, const int y_size, const plugin::Texture *texture);
private:
    int x;
    int y;

    sf::RenderTexture rt;
};
