#include "RenderTarget.h"

RenderTarget::RenderTarget(const int _x, const int _y)
  : x (_x),
    y (_y) 
{
    rt.create(x, y);
}

void RenderTarget::setPixel(const int x, const int y, const sf::Color color)
{
    sf::VertexArray point(sf::Points, 1);

    point[0].position = {x, y};
    point[0].color    = color;

    rt.draw(point);
}

void RenderTarget::drawLine(const int x1, const int y1, const int x2, const int y2, const sf::Color color)
{
    sf::VertexArray line(sf::LinesStrip, 2);

    line[0].position = {x1, y1};
    line[0].color    = color;

    line[1].position = {x2, y2};
    line[1].color    = color;

    rt.draw(line);
}

void RenderTarget::drawRect(const int x_lu, 
                            const int y_lu, 
                            const int x_size, 
                            const int y_size, 
                            const sf::Color fill_color,
                            const int line_thickness, 
                            const sf::Color out_color)
{
    // sf::RectangleShape rect(x_lu, y_lu);
    // rect.setPosition(start.toSfVector());
    // rect.setFillColor(fillColor.toSfColor());
    // rect.setOutlineColor(outColor.toSfColor());
    // rect.setOutlineThickness(OUTLINE_THICKNESS);
}

void RenderTarget::drawEllipse(const int x_lu, const int y_lu, const int x_size, const int y_size, const sf::Color color)
{

}

void RenderTarget::drawText(const int x, const int y, const char* const content, const uint16_t char_size, const sf::Color color)
{

}
