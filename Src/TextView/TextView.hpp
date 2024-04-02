#pragma once

#include <string>
#include <string_view>

#include "../Drawable.h"

class TextView : public Drawable 
{
public:
    explicit TextView(const int _x, const int _y, const std::string_view _content = "")
      : x       (_x),
        y       (_y),
        content (_content) {} 

    void draw(RenderTarget& render_target) override 
    { render_target.drawText(x, y, content.c_str(), kTextSize, kTextColor); }

    void setContent(const std::string_view _content) 
    { content = _content; }

private:
    const uint16_t  kTextSize  = 20;
    const sf::Color kTextColor = sf::Color::White;

private:
    int x;
    int y;
    std::string content;
};