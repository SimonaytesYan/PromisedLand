#pragma once

#include <cstdint>

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
    explicit RenderTarget(const Point size);

    void setPixel   (const Point pos , const sf::Color color);
    void drawLine   (const Point pos1, const Point pos2, const sf::Color color);
    void drawRect   (const Point lu, 
                     const Point size, 
                     const sf::Color fill_color,
                     const int line_thickness  = 0, 
                     const sf::Color out_color = sf::Color::Transparent);

    void drawCircle (const Point lu, 
                     const double radius, 
                     const sf::Color fill_color, 
                     const int line_thickness  = 0, 
                     const sf::Color out_color = sf::Color::Transparent);

    void drawText   (const Point pos, const char* const content, const uint16_t char_size, const sf::Color color);
    void drawTexture(const Point pos, const Texture& texture);

    void display();
    void display(sf::RenderWindow& window);

    void clear(const sf::Color clear_color = sf::Color::Transparent);

private:
    static constexpr char* const kDefaultFont = "Assets/arial.ttf";
    static constexpr char* const kOnOpenError = "Could not open file: ";

private:
    sf::RenderTexture rt;
    sf::Font          font;
};
