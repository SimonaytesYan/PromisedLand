#pragma once

#include <string>
#include <string_view>

#include "../Widget.hpp"

class TextView : public Widget 
{
public:
    explicit TextView(const Point _pos, const std::string_view _content = "")
      : Widget  (_pos),
        content (_content) {} 

    void draw(RenderTarget& render_target) override 
    { render_target.drawText(pos, content.c_str(), kTextSize, kTextColor); }

    void setContent(const std::string_view _content) 
    { content = _content; }

private:
    const uint16_t  kTextSize  = 20;
    const Color kTextColor = Color::White;

private:
    std::string content;
};