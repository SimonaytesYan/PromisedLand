#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <string_view>

#include "../Widget.hpp"

class TextView : public Widget 
{
public:
    explicit TextView(const Point _pos, const std::string_view _content = "", uint16_t text_size = 20)
      : Widget    (_pos),
        content   (_content),
        kTextSize (text_size) {} 

    void draw(RenderTarget& render_target) override 
    { render_target.drawText(pos, content.c_str(), kTextSize, text_color); }

    void push(const EventPtr event) override
    { }

    void setContent(const std::string_view _content) 
    { content = _content; }

    void setTextColor(Color new_color)
    {
        text_color = new_color;
    }

private:
    const uint16_t kTextSize  = 20;

private:
    Color       text_color = {255, 255, 255};
    std::string content;
};