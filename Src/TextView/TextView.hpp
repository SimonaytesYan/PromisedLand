#pragma once

#include "../Drawable.h"

class TextView : public Drawable {
public:
    explicit TextView(const char* _content)
      : content (_content) {} 

    void draw(RenderTarget& render_target) override 
    { render_target.drawText(x, y, content, kTextSize, kTextColor); }

    void setContent(const char* _content) 
    { content = _content; }

private:
    const uint16_t  kTextSize  = 20;
    const sf::Color kTextColor = sf::Color::White;

private:
    int x;
    int y;
    const char* content;
};