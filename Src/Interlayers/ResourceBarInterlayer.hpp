#pragma once

#include "LogicInterlayer.hpp"
#include "../Graphics/Widget/TextView/ResourceBar.hpp"

class ResourceBarInterlayer : public LogicInterlayer
{
public:
    ResourceBarInterlayer(ResourceBar& resources_bar) 
    : resources_bar (resources_bar)
    { }

    void pushToView(const EventPtr event)
    { resources_bar.push(event); }    

private:
    ResourceBar& resources_bar;
};
