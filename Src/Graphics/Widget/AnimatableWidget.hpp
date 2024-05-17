#pragma once

#include "Widget.hpp"
#include "../../../StlVector/Src/Vector.hpp"

class AnimatedWidget : public Widget
{
public:
    AnimatedWidget(const Point pos, Vector<Texture>&& images) : 
    Widget        (pos),
    images        (images),
    image_counter (0)
    { }

    AnimatedWidget(const Point pos, const Vector<const char*>& files) : 
    Widget        (pos),
    image_counter (0)
    {
        const size_t files_number = files.Size();
        for (size_t i = 0; i < files_number; i++)
            images.EmplaceBack(files[i]);
    }

    void draw(RenderTarget& rt) override
    {
        if (image_counter < images.Size())
            rt.drawTexture(pos, images[image_counter]);

        image_counter++;
        if (image_counter >= images.Size())
            image_counter = 0;
    }

    void push(EventPtr event) override
    { }

private:
    Vector<Texture> images;
    size_t          image_counter;
};
