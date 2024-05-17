#pragma once

#include "Widget.hpp"
#include "../../Utils/RenderTarget.hpp"

class ImageView : public Widget
{
public:
    explicit ImageView(const Point position, const char* img_path)
      : Widget  (position),
        texture (img_path)
    {}

    void push(const EventPtr event) override {}

    void draw(RenderTarget& render_target) override
    {
        render_target.drawTexture(pos, texture);
    }

private:
    const Texture texture;
};