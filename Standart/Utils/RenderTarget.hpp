#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "GraphicPrimitives.hpp"
#include "Utils.hpp"

// TODO: change

struct Texture 
{
    explicit Texture(const char* const img_path);

    sf::Texture sf_texture;
};

class RenderTarget
{
public:
    explicit RenderTarget(const Point size);

    virtual void setPixel   (const Point pos , const Color color);
    virtual void drawLine   (const Point pos1, const Point pos2, const Color color);
    virtual void drawRect   (const Point lu, 
                             const Point size, 
                             const Color fill_color,
                             const int line_thickness  = 0, 
                             const Color out_color = Color::Transparent);

    virtual void drawCircle (const Point lu, 
                             const double radius, 
                             const Color fill_color, 
                             const int line_thickness  = 0, 
                             const Color out_color = Color::Transparent);

    virtual void drawText   (const Point pos, const char* const content, const uint16_t char_size, const Color color);
    virtual void drawTexture(const Point pos, const Texture& texture);

    virtual void display();
    virtual void display(sf::RenderWindow& window);

    virtual void clear(const Color clear_color = Color::Transparent);

private:
    static constexpr char* const kDefaultFont = "Assets/arial.ttf";
    static constexpr char* const kOnOpenError = "Could not open file: ";

private:
    sf::RenderTexture rt;
    sf::Font          font;
};
