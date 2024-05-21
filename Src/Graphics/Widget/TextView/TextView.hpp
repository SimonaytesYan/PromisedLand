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
    { render_target.drawText(pos, content.c_str(), kTextSize, kTextColor); }

    void push(const EventPtr event) override
    { }

    void setContent(const std::string_view _content) 
    { content = _content; }

private:
    const uint16_t kTextSize  = 20;
    const Color    kTextColor = {255, 255, 255};

private:
    std::string content;
};