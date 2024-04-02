#include "RenderTarget.h"

Texture::Texture(const char* const img_path)
{
    if (img_path)
    {
        sf_texture.loadFromFile(img_path);
    }
}

RenderTarget::RenderTarget(const int _width, const int _height)
{
    PRINT_ON_ERROR(!font.loadFromFile(kDefaultFont), stderr, "%s %s\n", kOnOpenError, kDefaultFont);
    rt.create(_width, _height);
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
    sf::RectangleShape rect(sf::Vector2f(x_size, y_size));

    rect.setPosition        ({x_lu, y_lu});
    rect.setFillColor       (fill_color);
    rect.setOutlineColor    (out_color);
    rect.setOutlineThickness(line_thickness);

    rt.draw(rect);
}

void RenderTarget::drawCircle (const int x_lu, 
                 const int y_lu, 
                 const double radius, 
                 const sf::Color fill_color, 
                 const int line_thickness, 
                 const sf::Color out_color)
{
    sf::CircleShape circle(radius);

    circle.setPosition        ({x_lu, y_lu});
    circle.setFillColor       (fill_color);
    circle.setOutlineThickness(line_thickness);
    circle.setOutlineColor    (out_color);

    rt.draw(circle);
}

void RenderTarget::drawText(const int x, const int y, const char* const content, const uint16_t char_size, const sf::Color color)
{    
    sf::Text text_to_draw = sf::Text(content, font, char_size);

    text_to_draw.setFillColor(color);
    text_to_draw.setPosition ({x, y});

    rt.draw(text_to_draw);
}

void RenderTarget::drawTexture(const int x, const int y, const Texture& texture)
{
    sf::Vector2f rect_size = {texture.sf_texture.getSize().x, texture.sf_texture.getSize().y};
    sf::RectangleShape texture_rect(rect_size);

    texture_rect.setPosition({x, y});
    texture_rect.setTexture (&texture.sf_texture);

    rt.draw(texture_rect);
}

void RenderTarget::display()
{
    rt.display();
}

void RenderTarget::display(sf::RenderWindow& window)
{
    display();

    sf::Sprite to_draw_on_win(rt.getTexture());
    to_draw_on_win.setPosition(0, 0);

    window.draw(to_draw_on_win);
}

void RenderTarget::clear(const sf::Color clear_color)
{
    rt.clear(clear_color);
}