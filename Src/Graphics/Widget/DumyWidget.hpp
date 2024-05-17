#pragma once

#include <vector>

#include "Widget.hpp"

class DummyWidget : public Renderable
{
public:
    explicit DummyWidget()
      : drawable_children()
    {}

    void draw(RenderTarget& render_target) override
    {
        for (const auto child : drawable_children)
        {
            child->draw(render_target);
        }
    }

    void addChild(Renderable* child)
    {
        drawable_children.push_back(child);
    }

    void removeChild(const Renderable* child)
    {
        const auto child_it = std::find(drawable_children.begin(), drawable_children.end(), child);
        
        if (child_it != drawable_children.end())
        {
            drawable_children.erase(child_it);
        }
    }

private:
    std::vector<Renderable*> drawable_children;
};