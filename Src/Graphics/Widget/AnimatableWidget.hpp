#pragma once

#include <chrono>

#include "Widget.hpp"
#include "../../../StlVector/Src/Vector.hpp"

class AnimatedWidget : public Widget
{
    typedef std::chrono::_V2::system_clock::time_point time_point;
public:
    AnimatedWidget(const Point pos, Vector<Texture>&& images) : 
    Widget        (pos),
    images        (images),
    prev_time     (std::chrono::high_resolution_clock::now())
    { }

    AnimatedWidget(const Point pos, const Vector<const char*>& files) : 
    Widget        (pos),
    prev_time     (std::chrono::high_resolution_clock::now())
    {
        const size_t files_number = files.Size();
        for (size_t i = 0; i < files_number; i++)
            images.EmplaceBack(files[i]);
    }

    void draw(RenderTarget& rt) override
    {
        if (image_counter < images.Size())
            rt.drawTexture(pos, images[image_counter]);
        time_point now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(now - prev_time).count() > 100)
        {
            prev_time = now;

            image_counter++;
            if (image_counter >= images.Size())
                image_counter = 0;
        }
    }

    void setFrameDuration(const size_t new_frame_duration)
    {
        frame_duration = new_frame_duration;
    }

    void push(EventPtr event) override
    { }

private:
    size_t          image_counter  = 0;
    size_t          frame_duration = 100;
    Vector<Texture> images;
    time_point      prev_time;
};
