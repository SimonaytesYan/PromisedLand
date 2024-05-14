#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "GraphicPrimitives.hpp"
#include "Utils.hpp"
#include "../../Standart/Utils/RenderTargetI.hpp"

struct Texture : public TextureI
{
    explicit Texture(const char* const img_path);

    sf::Texture test;
};

class RenderTarget : public RenderTargetI
{
public:
    explicit RenderTarget(const Point size);

    void setPixel   (const Point pos , const Color color) override;
    void drawLine   (const Point pos1, const Point pos2, const Color color) override;
    void drawRect   (const Point lu, 
                             const Point size, 
                             const Color fill_color,
                             const int line_thickness  = 0, 
                             const Color out_color = {0, 0, 0, 0}) override;

    void drawCircle (const Point lu, 
                             const double radius, 
                             const Color fill_color, 
                             const int line_thickness  = 0, 
                             const Color out_color = {0, 0, 0, 0}) override;

    void drawText   (const Point pos, const char* const content, const uint16_t char_size, const Color color) override;
    void drawTexture(const Point pos, const TextureI& texture) override;
    void drawTexture(const Point pos, const size_t x_size, const size_t y_size, const TextureI& texture) override;

    void display() override;
    void display(sf::RenderWindow& window) override;

    void clear(const Color clear_color = {0, 0, 0, 0}) override;

    TextureI* getTexture() override;

private:
    static constexpr char* const kDefaultFont = "Assets/arial.ttf";
    static constexpr char* const kOnOpenError = "Could not open file: ";

private:
    sf::RenderTexture rt;
    sf::Font          font;
};
