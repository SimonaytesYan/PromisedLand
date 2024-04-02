#pragma once

#include <SFML/Graphics.hpp>

#include "Utils.hpp"

struct Texture 
{
    explicit Texture(const char* const img_path);

    sf::Texture sf_texture;
};

class RenderTarget
{
public:
    explicit RenderTarget(const int _width, const int _height);

    void setPixel   (const int x, const int y, const sf::Color color);
    void drawLine   (const int x1, const int y1, const int x2, const int y2, const sf::Color color);
    void drawRect   (const int x_lu, 
                     const int y_lu, 
                     const int x_size, 
                     const int y_size, 
                     const sf::Color fill_color,
                     const int line_thickness  = 0, 
                     const sf::Color out_color = sf::Color::Transparent);

    void drawCircle (const int x_lu, 
                     const int y_lu, 
                     const double radius, 
                     const sf::Color fill_color, 
                     const int line_thickness  = 0, 
                     const sf::Color out_color = sf::Color::Transparent);

    void drawText   (const int x, const int y, const char* const content, const uint16_t char_size, const sf::Color color);
    void drawTexture(const int x, const int y, const Texture& texture);

    void display();
    void display(sf::RenderWindow& window);

private:
    static constexpr char* const kDefaultFont = "Assets/arial.ttf";
    static constexpr char* const kOnOpenError = "Could not open file: ";

private:
    sf::RenderTexture rt;
    sf::Font          font;
};
