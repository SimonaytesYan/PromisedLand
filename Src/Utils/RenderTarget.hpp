#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "GraphicPrimitives.hpp"
#include "Utils.hpp"

struct Texture 
{
    explicit Texture(const sf::Texture& _sf_texture)
      : sf_texture (_sf_texture),
        _img_path  ("")
    {}

    explicit Texture(const char* const img_path)
      :  _img_path (img_path)
    {
      if (img_path)
      {
        sf_texture.loadFromFile(img_path);
      }
    }

    sf::Texture sf_texture;
    const char* _img_path;
};

class RenderTarget
{
public:
    explicit RenderTarget(const Point size);

    void setPixel   (const Point pos , const Color color);
    void drawLine   (const Point pos1, const Point pos2, const Color color);
    void drawRect   (const Point lu, 
                             const Point size, 
                             const Color fill_color,
                             const int line_thickness  = 0, 
                             const Color out_color = {0, 0, 0, 0});

    void drawCircle (const Point lu, 
                             const double radius, 
                             const Color fill_color, 
                             const int line_thickness  = 0, 
                             const Color out_color = {0, 0, 0, 0});

    void drawText   (const Point pos, const char* const content, const uint16_t char_size, const Color color);
    void drawTexture(const Point pos, const Texture& texture);
    void drawTexture(const Point original_pos, const Point relative_pos, const size_t x_size, const size_t y_size, const Texture& texture);

    void display();
    void display(sf::RenderWindow& window);

    void clear(const Color clear_color = {0, 0, 0, 0});

    Texture* getTexture();

private:
    static constexpr char* const kDefaultFont = "Assets/arial.ttf";
    static constexpr char* const kOnOpenError = "Could not open file: ";

private:
    sf::RenderTexture rt;
    sf::Font          font;
};
