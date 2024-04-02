#pragma once

class EventProcessable
{
public:
    virtual void onClick(int x, int y) = 0;
    virtual void onTick() = 0;
    virtual ~EventProcessable() = default;
};
