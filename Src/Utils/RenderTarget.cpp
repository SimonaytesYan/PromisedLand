#include "RenderTarget.hpp"

Texture::Texture(const char* const img_path)
{
    if (img_path)
    {
        sf_texture.loadFromFile(img_path);
    }
}

RenderTarget::RenderTarget(const Point size)
{
    PRINT_ON_ERROR(!font.loadFromFile(kDefaultFont), stderr, "%s %s\n", kOnOpenError, kDefaultFont);
    rt.create(size.x, size.y);
}

void RenderTarget::setPixel(const Point pos, const Color color)
{
    sf::VertexArray point(sf::Points, 1);

    point[0].position = pos;
    point[0].color    = color;

    rt.draw(point);
}

void RenderTarget::drawLine(const Point pos1, const Point pos2, const Color color)
{
    sf::VertexArray line(sf::LinesStrip, 2);

    line[0].position = pos1;
    line[0].color    = color;

    line[1].position = pos2;
    line[1].color    = color;

    rt.draw(line);
}

void RenderTarget::drawRect(const Point lu, 
                            const Point size, 
                            const Color fill_color,
                            const int line_thickness, 
                            const Color out_color)
{
    sf::RectangleShape rect(size);

    rect.setPosition        (lu);
    rect.setFillColor       (fill_color);
    rect.setOutlineColor    (out_color);
    rect.setOutlineThickness(line_thickness);

    rt.draw(rect);
}

void RenderTarget::drawCircle (const Point lu, 
                               const double radius, 
                               const Color fill_color, 
                               const int line_thickness, 
                               const Color out_color)
{
    sf::CircleShape circle(radius);

    circle.setPosition        (lu);
    circle.setFillColor       (fill_color);
    circle.setOutlineThickness(line_thickness);
    circle.setOutlineColor    (out_color);

    rt.draw(circle);
}

void RenderTarget::drawText(const Point pos, const char* const content, const uint16_t char_size, const Color color)
{    
    sf::Text text_to_draw = sf::Text(content, font, char_size);

    text_to_draw.setFillColor(color);
    text_to_draw.setPosition (pos);

    rt.draw(text_to_draw);
}

void RenderTarget::drawTexture(const Point pos, const Texture& texture)
{
    sf::Vector2f rect_size = {texture.sf_texture.getSize().x, texture.sf_texture.getSize().y};
    sf::RectangleShape texture_rect(rect_size);

    texture_rect.setPosition(pos);
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

void RenderTarget::clear(const Color clear_color)
{
    rt.clear(clear_color);
}