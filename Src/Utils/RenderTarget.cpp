#include <SFML/Graphics.hpp>

#include "RenderTarget.hpp"

const Color Color::Black      (  0,   0,   0);
const Color Color::White      (255, 255, 255);
const Color Color::Red        (255,   0,   0);
const Color Color::Green      (  0, 255,   0);
const Color Color::Blue       (  0,   0, 255);
const Color Color::Yellow     (255, 255,   0);
const Color Color::Magenta    (214,   0, 110);
const Color Color::Cyan       (  0, 255, 255);
const Color Color::Transparent(  0,   0,   0, 0);

RenderTarget::RenderTarget(const Point size)
{
    PRINT_ON_ERROR(!font.loadFromFile(kDefaultFont), stderr, "%s %s\n", kOnOpenError, kDefaultFont);
    rt.create(size.x, size.y);
}

void RenderTarget::setPixel(const Point pos, const Color color)
{
    sf::VertexArray point(sf::Points, 1);

    point[0].position = {pos.x, pos.y};
    point[0].color    = {color.r, color.g, color.b, color.a};

    rt.draw(point);
}

void RenderTarget::drawLine(const Point pos1, const Point pos2, const Color color)
{
    sf::VertexArray line(sf::LinesStrip, 2);

    line[0].position = {pos1.x, pos1.y};
    line[0].color    = {color.r, color.g, color.b, color.a};

    line[1].position = {pos2.x, pos2.y};
    line[1].color    = {color.r, color.g, color.b, color.a};

    rt.draw(line);
}

void RenderTarget::drawRect(const Point lu, 
                            const Point size, 
                            const Color fill_color,
                            const int line_thickness, 
                            const Color out_color)
{
    sf::RectangleShape rect({size.x, size.y});

    rect.setPosition        ({lu.x, lu.y});
    rect.setFillColor       ({fill_color.r, fill_color.g, fill_color.b, fill_color.a});
    rect.setOutlineColor    ({out_color.r, out_color.g, out_color.b, out_color.a});
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

    circle.setPosition        ({lu.x, lu.y});
    circle.setFillColor       ({fill_color.r, fill_color.g, fill_color.b, fill_color.a});
    circle.setOutlineThickness(line_thickness);
    circle.setOutlineColor    ({out_color.r, out_color.g, out_color.b, out_color.a});

    rt.draw(circle);
}

void RenderTarget::drawText(const Point pos, const char* const content, const uint16_t char_size, const Color color)
{    
    sf::Text text_to_draw = sf::Text(content, font, char_size);

    text_to_draw.setFillColor({color.r, color.g, color.b, color.a});
    text_to_draw.setPosition ({pos.x, pos.y});

    rt.draw(text_to_draw);
}

void RenderTarget::drawTexture(const Point pos, const Texture& texture)
{
    sf::Vector2f rect_size = {texture.sf_texture.getSize().x, texture.sf_texture.getSize().y};
    sf::RectangleShape texture_rect(rect_size);

    texture_rect.setPosition({pos.x, pos.y});
    texture_rect.setTexture (&texture.sf_texture);

    rt.draw(texture_rect);
}

void RenderTarget::drawTexture(const Point original_pos, const Point relative_pos, const size_t x_size, const size_t y_size, const Texture& texture)
{
    const size_t texture_size_x = texture.sf_texture.getSize().x;
    const size_t texture_size_y = texture.sf_texture.getSize().y;

    sf::Sprite sprite_to_crop(texture.sf_texture);
    sprite_to_crop.setPosition({original_pos.x, original_pos.y});

    sf::RenderTexture main_rt_copy;

    main_rt_copy.create (texture_size_x, texture_size_y);
    main_rt_copy.draw   (sprite_to_crop);
    main_rt_copy.display();

    sf::Sprite cropped_img(main_rt_copy.getTexture(), sf::IntRect(relative_pos.x, relative_pos.y, x_size, y_size));
    cropped_img.setPosition({original_pos.x, original_pos.y});

    rt.draw(cropped_img);
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
    rt.clear({clear_color.r, clear_color.g, clear_color.b, clear_color.a});
}

// delete after use
Texture* RenderTarget::getTexture() 
{
    return new Texture(rt.getTexture());
}

Color getTextureMeanColor(const char* asset_path)
{
    sf::Image asset_img;
    asset_img.loadFromFile(asset_path);

    const sf::Uint8* pixels = asset_img.getPixelsPtr();
    size_t r = 0, g = 0, b = 0, a = 0;

    const size_t texture_size = asset_img.getSize().x * asset_img.getSize().y;
    for (size_t i = 0; i < texture_size; ++i) 
    {
        r += pixels[4 * i + 0];
        g += pixels[4 * i + 1];
        b += pixels[4 * i + 2];
        a += pixels[4 * i + 3];
    }

    return {static_cast<unsigned char>(r / texture_size), 
            static_cast<unsigned char>(g / texture_size), 
            static_cast<unsigned char>(b / texture_size), 
            static_cast<unsigned char>(a / texture_size)};
}