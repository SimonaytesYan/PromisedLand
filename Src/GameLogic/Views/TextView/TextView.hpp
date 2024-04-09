#pragma once

#include <string>
#include <string_view>

#include "../../Renderable.hpp"

class TextView : public Renderable 
{
public:
    explicit TextView(const Point _pos, const std::string_view _content = "")
      : pos     (_pos),
        content (_content) {} 

    void draw(RenderTarget& render_target) override 
    { render_target.drawText(pos, content.c_str(), kTextSize, kTextColor); }

    void setContent(const std::string_view _content) 
    { content = _content; }

private:
    const uint16_t  kTextSize  = 20;
    const sf::Color kTextColor = sf::Color::White;

private:
    Point       pos;
    std::string content;
};