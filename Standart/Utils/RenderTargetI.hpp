#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "GraphicPrimitives.hpp"
#include "Utils.hpp"

// TODO: change

struct TextureI 
{
    explicit TextureI(const char* const img_path)
      :  _img_path (img_path)
    {}

    sf::Texture sf_texture;
    const char* _img_path;
};

class RenderTargetI
{
public:
    virtual void setPixel   (const Point pos , const Color color) = 0;
    virtual void drawLine   (const Point pos1, const Point pos2, const Color color) = 0;
    virtual void drawRect   (const Point lu, 
                             const Point size, 
                             const Color fill_color,
                             const int line_thickness  = 0, 
                             const Color out_color = {0, 0, 0, 0}) = 0;

    virtual void drawCircle (const Point lu, 
                             const double radius, 
                             const Color fill_color, 
                             const int line_thickness  = 0, 
                             const Color out_color = {0, 0, 0, 0}) = 0;

    virtual void drawText   (const Point pos, const char* const content, const uint16_t char_size, const Color color) = 0;
    virtual void drawTexture(const Point pos, const TextureI& texture) = 0;

    virtual void display() = 0;
    virtual void display(sf::RenderWindow& window) = 0;

    virtual void clear(const Color clear_color = {0, 0, 0, 0}) = 0;
};
